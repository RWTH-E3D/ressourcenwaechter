// ==== Serial output via Serial 0 for debugging in Nextion HMI software ====

// basic data for Nextion touch display via serial 0 (USB) to debug in HMI software
// Nextion display uses 3 times 0xff as the end of each command
void output_to_nextion_debug() {
  // sys info
  Serial.print("version.txt=\"");        Serial.print(version);Serial.print("\"");          Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("time.txt=\"");           Serial.print(time_now_str);Serial.print("\"");     Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("is_sleep.val=");         Serial.print(isSleep);                             Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("sd_ava.val=");           Serial.print(SDisAvailable);                       Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("sd_used.val=");          Serial.print(sdUsedPercentage);                    Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  // user data
  Serial.print("level.val=");            Serial.print(level);                               Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("expNow.val=");           Serial.print(expNow);                              Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("expNext.val=");          Serial.print(expNext);                             Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  // window sensor
  Serial.print("window_ava.val=");       Serial.print(WindowSensorisAvailable);             Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("window_is_open.val=");   Serial.print(w_isOpen);                            Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  // Power/current sensor
  Serial.print("power_ava.val=");        Serial.print(PowerSensorisAvailable);              Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("poweradc.val=");         Serial.print(powerADCValue * 100, 0);              Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("power.val=");            Serial.print(power * 100, 0);                      Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  // BME280
  Serial.print("bme280_ava.val=");       Serial.print(BME280isAvailable);                   Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("temperature.val=");      Serial.print(temperature * 100, 0);                Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("humidity.val=");         Serial.print(humidity * 100, 0);                   Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("pressure.val=");         Serial.print(pressure * 100, 0);                   Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  // DS18B20
  Serial.print("radtemp_ava.val=");      Serial.print(RadTempSensorisAvailable);            Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("radtemp.val=");          Serial.print(radTemperature * 100, 0);             Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  // SGP40
  Serial.print("sgp40_ava.val=");        Serial.print(SGP40isAvailable);                    Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("voc.val=");              Serial.print(vocIndex);                            Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  // VEML7700
  Serial.print("veml7700_ava.val=");     Serial.print(VEML7700isAvailable);                 Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("light.val=");            Serial.print(light * 100, 0);                      Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  // Sound sensor
  Serial.print("sound_ava.val=");        Serial.print(SoundSensorisAvailable);              Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("sound.val=");            Serial.print(sound * 100, 0);                      Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  // Wind speed sensor
  Serial.print("windspeed_ava.val=");    Serial.print(WindSensorisAvailable);               Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("wind_speed.val=");        Serial.print(windSpeed * 100, 0);                  Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  // SCD30
  Serial.print("scd30_ava.val=");        Serial.print(SCD30isAvailable);                    Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("co2.val=");              Serial.print(co2 * 100, 0);                        Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  // predicted comfort
  Serial.print("tci.val=");              Serial.print(TCI_val * 100, 0);                    Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("sci.val=");              Serial.print(SCI_val * 100, 0);                    Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("lci.val=");              Serial.print(LCI_val * 100, 0);                    Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("pci.val=");              Serial.print(PCI_val * 100, 0);                    Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("iaqi.val=");             Serial.print(IAQI_val * 100, 0);                   Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
  Serial.print("ieqi.val=");             Serial.print(IEQI_val * 100, 0);                   Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
}
