// ==== Serial output via USB (Serial 0) ====

void output() {
  // separate output timer and get data timer for higher flexibility.
  // by default they are same.
  if(millis() - previousMillis_output >= updateInterval) {
    previousMillis_output = millis();
    output_to_nextion();

#ifdef DEBUG_MODE_IN_NEXTION_HMI
    output_to_nextion_debug();
#else
    output_serial();
#endif
    
    save_data();
  }
}

// contains more data than output_to_nextion() via serial 0
void output_serial() {
  // sys info
  Serial.print("version=");Serial.print(version);Serial.print(";");
  Serial.print("unixtime=");Serial.print(time_now.unixtime());Serial.print(";");
  Serial.print("time=");Serial.print(time_now_str);Serial.print(";");
  Serial.print("is_sleep=");Serial.print(isSleep);Serial.print(";");
  Serial.print("sd_available=");Serial.print(SDisAvailable);Serial.print(";");
  Serial.print("sd_used=");Serial.print(sdUsedPercentage);Serial.print(";");
  // user data
  Serial.print("level=");Serial.print(level);Serial.print(";");
  Serial.print("expNow=");Serial.print(expNow);Serial.print(";");
  Serial.print("expNext=");Serial.print(expNext);Serial.print(";");
  // window sensor
  Serial.print("windowsensor_available=");Serial.print(WindowSensorisAvailable);Serial.print(";");
  Serial.print("window_is_open=");Serial.print(w_isOpen);Serial.print(";");
  // Power/current sensor
  Serial.print("powersensor_available=");Serial.print(PowerSensorisAvailable);Serial.print(";");
  Serial.print("powerADCValue=");Serial.print(powerADCValue);Serial.print(";");
  Serial.print("Irms=");Serial.print(Irms);Serial.print(";");
  Serial.print("power=");Serial.print(power);Serial.print(";");
  // BME280
  Serial.print("bme280_available=");Serial.print(BME280isAvailable);Serial.print(";");
  Serial.print("temperature=");Serial.print(temperature);Serial.print(";");
  Serial.print("humidity=");Serial.print(humidity);Serial.print(";");
  Serial.print("pressure=");Serial.print(pressure);Serial.print(";");
  // DS18B20
  Serial.print("radTemp_available=");Serial.print(RadTempSensorisAvailable);Serial.print(";");
  Serial.print("radTemperature=");Serial.print(radTemperature);Serial.print(";");
  // SGP40
  Serial.print("sgp40_available=");Serial.print(SGP40isAvailable);Serial.print(";");
  Serial.print("voc=");Serial.print(vocIndex);Serial.print(";");
  // VEML7700
  Serial.print("veml7700_available=");Serial.print(VEML7700isAvailable);Serial.print(";");
  Serial.print("light=");Serial.print(light);Serial.print(";");
  // Sound sensor
  Serial.print("soundsensor_available=");Serial.print(SoundSensorisAvailable);Serial.print(";");
  Serial.print("sound=");Serial.print(sound);Serial.print(";");
  // Wind speed sensor
  Serial.print("windsensor_available=");Serial.print(WindSensorisAvailable);Serial.print(";");
  Serial.print("wind_speed=");Serial.print(windSpeed);Serial.print(";");
  Serial.print("RV_Wind_Volts=");Serial.print(RV_Wind_Volts);Serial.print(";");
  Serial.print("zeroWind_volts=");Serial.print(zeroWind_volts);Serial.print(";");
  // SCD30
  Serial.print("scd30_available=");Serial.print(SCD30isAvailable);Serial.print(";");
  Serial.print("co2=");Serial.print(co2);Serial.print(";");
  // predicted comfort
  Serial.print("tci=");Serial.print(TCI_val);Serial.print(";");
  Serial.print("sci=");Serial.print(SCI_val);Serial.print(";");
  Serial.print("lci=");Serial.print(LCI_val);Serial.print(";");
  Serial.print("pci=");Serial.print(PCI_val);Serial.print(";");
  Serial.print("iaqi=");Serial.print(IAQI_val);Serial.print(";");
  Serial.print("ieqi=");Serial.print(IEQI_val);Serial.println(";");
}
