// ==== Save relevant settings ====

void save_settings () {
  if (SDisAvailable) {
    // settings
    char settings_data[1000];
    sprintf(
      settings_data, 
      "tempAdj[degC]:%.2f;"
      "humAdj[percent]:%.2f;"
      "presAdj[hPa]:%.2f;"
      "radTempAdj[degC]:%.2f;"
      "lightAdjA[lux]:%.2f;"
      "lightAdjB[lux]:%.2f;"
      "soundAdj[-]:%.2f;"
      "zeroWindAdj[-]:%.2f;"
      "updIntDefault[ms]:%d;"
      "updIntSleep[ms]:%d;"
      "powerVolt[V]:%d;"
      "met:%.2f;"
      "clo:%.2f;"
      "TCIw:%.2f;"
      "SCIw:%.2f;"
      "LCIw:%.2f;"
      "PCIw:%.2f;"
      "IAQIw:%.2f;"
      "presMoComfMin:%.1f;"
      "presMoComfMax:%.1f;"
      "presComfMin:%.1f;"
      "presComfMax:%.1f;"
      "presNoComfMin:%.1f;"
      "presNoComfMax:%.1f;"
      "vocGoodMax:%.1f;"
      "vocModerateMax:%.1f;"
      "vocUnhealthyMax:%.1f;"
      "co2GoodMax:%.1f;"
      "co2ModerateMax:%.1f;"
      "co2UnhealthyMax:%.1f;"
      "lightMoComfMin:%.1f;"
      "lightComfMin:%.1f;"
      "lightNoComfMin:%.1f;"
      "soundMoComfMax:%.1f;"
      "soundComfMax:%.1f;"
      "soundNoComfMax:%.1f;"
      "windspMoComfMax:%.1f;"
      "windspComfortMax:%.1f;"
      "windspNoComfortMax:%.1f;", 
      temperatureAdjustment, 
      humidityAdjustment, 
      pressureAdjustment, 
      radTemperatureAdjustment,
      lightAdjustment_A,
      lightAdjustment_B, 
      soundAdjustment, 
      zeroWindAdjustment, 
      updateIntervalDefault, 
      updateIntervalSleep,
      powerVoltage,
      met,
      clo,
      TCI_weight,
      SCI_weight,
      LCI_weight,
      PCI_weight,
      IAQI_weight,
      pressure_most_comfort_min,
      pressure_most_comfort_max,
      pressure_comfort_min,
      pressure_comfort_max,
      pressure_not_comfort_min,
      pressure_not_comfort_max,
      voc_good_max,
      voc_moderate_max,
      voc_unhealthy_max,
      co2_good_max,
      co2_moderate_max,
      co2_unhealthy_max,
      light_most_comfort_min,
      light_comfort_min,
      light_not_comfort_min,
      sound_most_comfort_max,
      sound_comfort_max,
      sound_not_comfort_max,
      wind_speed_most_comfort_max,
      wind_speed_comfort_max,
      wind_speed_not_comfort_max
    );
    if (!SD.exists(filename_settings)){
      // create setting file if not exists
      sd_write(filename_settings, settings_data);
      debug_println("SD card check: settings txt created!");
    } else {
      debug_println("SD card check: settings txt already exists!");
      // still overwrite if exists cause settings could be changed during calibration
      sd_write(filename_settings, settings_data);
      debug_println("SD card check: settings txt updated!");
    }
    
    delay(200);
    
    // user data
    char userdata[200];
    if (!SD.exists(filename_userdata)){
      // create user data file if not exists
      sprintf(userdata, userdata_default);
      sd_write(filename_userdata, userdata);
      debug_println("SD card check: userdata created!");
    } else {
      debug_println("SD card check: userdata already exists!");
      // do not overwrite if exists.
      // If new user, change sd card or backup and then delete the previous user data file in sd card.
      // read user data for level system
      read_usrdata();
    }
  }
}

void read_usrdata() {
#ifdef DEBUG_MODE   
  Serial.printf("SD - Reading file: %s\n", filename_userdata);
#endif
  
  File usrfile = SD.open(filename_userdata, FILE_READ);
  
  if(usrfile){
    // read level and exp info and save into lvExpArray
    // lvExpArray[0] = level
    // lvExpArray[1] = exp
    char record[30];
    byte recordNum;
    byte charNum;
    while (usrfile.available()) {
      char inChar = usrfile.read();
      if (inChar == ';') {
        strcpy(lvExpArray[recordNum], record);
        recordNum++;
        charNum = 0;
      } else {
        record[charNum++] = inChar;
        record[charNum] = '\0';  
      }
    }
    usrfile.close();
    level = atoi(lvExpArray[0]);
    expNow = atoi(lvExpArray[1]);
  } else {
    debug_println("SD - Error: failed to open user data file for reading!");
  }
#ifdef DEBUG_MODE
  Serial.println("SD - User data successfully loaded!");
  Serial.printf("Level: %d; EXP: %d;\n", level, expNow);
#endif
}
