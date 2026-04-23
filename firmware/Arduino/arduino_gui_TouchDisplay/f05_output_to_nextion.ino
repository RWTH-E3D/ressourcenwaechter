// ==== Serial output via Serial 2 (between MC and Nextion display) ====

// basic data for Nextion touch display via serial 2
// Nextion display uses 3 times 0xff as the end of each command
void output_to_nextion() {
  // sys info
  Serial2.print("version.txt=\"");        Serial2.print(version);Serial2.print("\"");         Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("time.txt=\"");           Serial2.print(time_now_str);Serial2.print("\"");    Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("is_sleep.val=");         Serial2.print(isSleep);                             Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("sd_ava.val=");           Serial2.print(SDisAvailable);                       Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("sd_used.val=");          Serial2.print(sdUsedPercentage);                    Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  // user data
  Serial2.print("level.val=");            Serial2.print(level);                               Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("expNow.val=");           Serial2.print(expNow);                              Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("expNext.val=");          Serial2.print(expNext);                             Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  // window sensor
  Serial2.print("window_ava.val=");       Serial2.print(WindowSensorisAvailable);             Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("window_is_open.val=");   Serial2.print(w_isOpen);                            Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  // Power/current sensor
  Serial2.print("power_ava.val=");        Serial2.print(PowerSensorisAvailable);              Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("poweradc.val=");         Serial2.print(powerADCValue * 100, 0);              Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("power.val=");            Serial2.print(power * 100, 0);                      Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  // BME280
  Serial2.print("bme280_ava.val=");       Serial2.print(BME280isAvailable);                   Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("temperature.val=");      Serial2.print(temperature * 100, 0);                Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("humidity.val=");         Serial2.print(humidity * 100, 0);                   Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("pressure.val=");         Serial2.print(pressure * 100, 0);                   Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  // DS18B20
  Serial2.print("radtemp_ava.val=");      Serial2.print(RadTempSensorisAvailable);            Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("radtemp.val=");          Serial2.print(radTemperature * 100, 0);             Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  // SGP40
  Serial2.print("sgp40_ava.val=");        Serial2.print(SGP40isAvailable);                    Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("voc.val=");              Serial2.print(vocIndex);                            Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  // VEML7700
  Serial2.print("veml7700_ava.val=");     Serial2.print(VEML7700isAvailable);                 Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("light.val=");            Serial2.print(light * 100, 0);                      Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  // Sound sensor
  Serial2.print("sound_ava.val=");        Serial2.print(SoundSensorisAvailable);              Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("sound.val=");            Serial2.print(sound * 100, 0);                      Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  // Wind speed sensor
  Serial2.print("windspeed_ava.val=");    Serial2.print(WindSensorisAvailable);               Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("wind_speed.val=");        Serial2.print(windSpeed * 100, 0);                  Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  // SCD30
  Serial2.print("scd30_ava.val=");        Serial2.print(SCD30isAvailable);                    Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("co2.val=");              Serial2.print(co2 * 100, 0);                        Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  // predicted comfort
  Serial2.print("tci.val=");              Serial2.print(TCI_val * 100, 0);                    Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("sci.val=");              Serial2.print(SCI_val * 100, 0);                    Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("lci.val=");              Serial2.print(LCI_val * 100, 0);                    Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("pci.val=");              Serial2.print(PCI_val * 100, 0);                    Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("iaqi.val=");             Serial2.print(IAQI_val * 100, 0);                   Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
  Serial2.print("ieqi.val=");             Serial2.print(IEQI_val * 100, 0);                   Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
}
