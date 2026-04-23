// ==== Get data from sensors ====

void get_data(){
  // get sensor data every "updateInterval" seconds
  if (millis() - previousMillis >= updateInterval) {
    status_updated = true;
    previousMillis = millis();
    counter_sd++;
    // T/H/P
    if (BME280isAvailable) {
      temperature = bme.readTemperature() + temperatureAdjustment;          // degC
      pressure = bme.readPressure() / 100.0 + pressureAdjustment;        // Pa -> hPa
      humidity = bme.readHumidity() + humidityAdjustment;                // %
    } else {
      temperature = -100;
      pressure = -100;
      humidity = -100;
    }
    
    // VOC
    if (SGP40isAvailable && BME280isAvailable) {
      vocRaw = sgp.measureRaw(temperature, humidity);
      vocIndex = sgp.measureVocIndex(temperature, humidity);
    } else if (SGP40isAvailable) {
      vocRaw = sgp.measureRaw(22, 50);   // if BME280 is not available, use default temperature and humidity value for SGP40 sensor
      vocIndex = sgp.measureVocIndex(22, 50);
    } else {
      vocIndex = -100;
    }
    
    // sound
    if (SoundSensorisAvailable) {
      // read multiple times for denoising, more reads means less noise, but slower
      long int adc_sound = 0;
      for (int i=0; i<loop_sound; i++) {
        adc_sound += analogRead(analogPinSoundSensor);
      }
      // get average adc value, +0.5 for round up instead of round down
      voltageValue = (adc_sound / loop_sound + 0.5) / ADCrange * VREF;
      // convert voltage to decibel value [dB(A)], linear relation between voltage and dB(A), see dfrobot wiki
      sound = voltageValue * 50.0 + soundAdjustment;
    } else {
      sound = -100;
    }
    
    // light
    if (VEML7700isAvailable) {
      lightRaw = veml.readLux();
      light = (0.0009 * sq(lightRaw) + 1.1171 * lightRaw + 28.449) * lightAdjustment_A + lightAdjustment_B;
    } else {
      light = -100;
    }
    
    // wind speed
    if (WindSensorisAvailable) {
      // read multiple times for denoising, more reads means less noise, but slower
      long int adc_windspeed_tmp = 0;
      long int adc_windspeed_rv = 0;
      for (int i=0; i<loop_windspeed; i++) {
        adc_windspeed_tmp += analogRead(analogPinForTMP);
        adc_windspeed_rv += analogRead(analogPinForRV);
      }
      // get average adc value, +0.5 for round up instead of round down
      TMP_Therm_ADunits = adc_windspeed_tmp / loop_windspeed + 0.5; 
      RV_Wind_ADunits = adc_windspeed_rv / loop_windspeed + 0.5;
      RV_Wind_Volts = RV_Wind_ADunits * VREF / ADCrange;  // VREF / ADCrange instead of 0.0048828125, in our case it's 3.3 / 4095 (12-bit ADC, 3.3V ESP32)
      
      /* -------------- Method 1 --------------
       * Regression function provided by the manufacturer
       * https://github.com/moderndevice/Wind_Sensor
       * Add averaging sampling for denoising
       * -------------------------------------- */
      // these are all derived from regressions from raw data as such they depend on a lot of experimental factors
      // such as accuracy of temp sensors, and voltage at the actual wind sensor, (wire losses) which were unaccouted for.
      TempCtimes100 = (0.005 *(TMP_Therm_ADunits * TMP_Therm_ADunits)) - (16.862 * TMP_Therm_ADunits) + 9075.4;  
      zeroWind_ADunits = -0.0006*(TMP_Therm_ADunits * TMP_Therm_ADunits) + 1.0727 * TMP_Therm_ADunits + 47.172;  //  13.0C  553  482.39
      zeroWind_volts = zeroWind_ADunits * VREF / ADCrange - zeroWindAdjustment; // VREF / ADCrange instead of 0.0048828125, in our case it's 3.3 / 4095 (12-bit ADC, 3.3V ESP32)
      // This from a regression from data in the form of 
      // Vraw = V0 + b * WindSpeed ^ c
      // V0 is zero wind at a particular temperature
      // The constants b and c were determined by some Excel wrangling with the solver.
      // windSpeed_MPH =  pow(((RV_Wind_Volts - zeroWind_volts) /.2300) , 2.7265); // unit mph, Note by QiH: outputs nan due to math error if zeroWindo_volts is bigger than RV_Wind_Volts.
      // Edited version to avoid wind speed < 0 m/s:
      float volts_base = RV_Wind_Volts - zeroWind_volts;
      if(volts_base < 0){volts_base = 0;}
      windSpeed_MPH =  pow((volts_base /0.23) , 2.7265);
      windSpeed = windSpeed_MPH * 0.44704; // mph -> m/s

      /* --------------------------------------
       * For other methods, please check windsensor_rev_p_vs_c.ino
       * -------------------------------------- */
      
    } else {
      windSpeed = -100;
    }
    
    // CO2
    if (SCD30isAvailable) {
      co2 = scd30.getCO2();
    } else {
      co2 = -100;
    }

    // radiation temperature
    if (RadTempSensorisAvailable) {
      RadTempSensor.requestTemperatures();
      radTemperature = RadTempSensor.getTempCByIndex(0) + radTemperatureAdjustment; // first sensor on one wire bus, degC
    } else {
      radTemperature = -100;
    }

    // window sensor
    if (WindowSensorisAvailable) {
      if(digitalRead(digitalPinReedSwitch) == HIGH){w_isOpen = false;}
      else{w_isOpen = true;}
    } else {
      w_isOpen = false;
    }

    // power/current sensor
    if (PowerSensorisAvailable) {
      if (PowerSensorCurrentOutput) {
        // model with current signal output (mA)
        // read multiple times for denoising, more reads means less noise, but slower
        // based on algorithm from EmonLib (openenergymonitor) - calcIrms()

        long int adc_power = 0; // buffer for adc values
        for (int i=0; i<loop_power; i++)
        {
          sampleI = analogRead(analogPinPowerSensor);
          adc_power += sampleI; // store adc values in buffer

          // Digital low pass filter extracts the 2.5 V or 1.65 V dc offset,
          // then subtract this - signal is now centered on 0 counts.
          offsetI = (offsetI + (sampleI-offsetI)/1024);
          filteredI = sampleI - offsetI;
      
          // Root-mean-square method current
          // 1) square current values
          sqI = filteredI * filteredI;
          // 2) sum
          sumI += sqI;
        }
        // get average adc value, +0.5 for round up instead of round down
        powerADCValue = (adc_power / loop_power + 0.5) / ADCrange * VREF; // raw voltage signal
      
        double I_RATIO = ICAL *(SupplyVoltage / ADCrange);
        Irms = I_RATIO * sqrt(sumI / loop_power);
        power = Irms * powerVoltage;
        //Reset accumulators
        sumI = 0;
//        
//        
//        for (int i=0; i<loop_power; i++) {
//          adc_power += analogRead(analogPinPowerSensor);
//        }
//        // get average adc value, +0.5 for round up instead of round down
//        powerVoltageValue = (adc_power / loop_power + 0.5) / ADCrange * VREF; // raw voltage signal
//        
//        // map ADC voltage value to current value, e.g. 0-4095 -> 0-100A
//        int Vmax = currentOutputRange * senseResistor;
//        float powerPercent = powerVoltageValue / Vmax;


//        Irms = powerPercent * powerMeasurementRange + currentAdjustment;
        
      } else {
        // TODO: test model with voltage signal output (V)
        
      }
    } else {
      power = -100;
    }
    
    // RTC
    time_now = rtc.now();
    sprintf(time_now_str, "%s %02d:%02d:%02d-%02d.%02d.%04d", days[time_now.dayOfTheWeek()], time_now.hour(), time_now.minute(), time_now.second(), time_now.day(), time_now.month(), time_now.year());

    // SD card, update sd card usage info after reading data 40 times (if 15s interval -> 10min)
    if (SDisAvailable && counter_sd > 40) {
      sdUsedPercentage = int(SD.usedBytes() * 100 / SD.totalBytes());
      counter_sd = 0;
    }
    
  }
}
