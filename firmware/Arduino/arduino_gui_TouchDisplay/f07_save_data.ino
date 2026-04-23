// ==== Save all data ====

void save_data() {
  if (SDisAvailable) {
    // sensor data
    char filename_data[14];
    // filename using date to avoid a single big file
    // one csv file per day
    // format: yyyymmdd.csv
    sprintf(filename_data, "/%04d%02d%02d.csv", time_now.year(), time_now.month(), time_now.day());

    char data_header[] = "version," 
                         "unixtime,"
                         "time,"
                         "is_sleep[t/f],"
                         "windowsensor_available[t/f],"
                         "window_is_open[t/f],"
                         "powersensor_available[t/f],"
                         "powerADCValue[V],"
                         "power[W],"
                         "temperature[degC],"
                         "humidity[%],"
                         "pressure[hPa],"
                         "radiationTemp[degC],"
                         "voci[0-500],"
                         "light[lux],"
                         "sound[dBA],"
                         "wind_speed[m/s],"
                         "co2[ppm],"
                         "tci[0-3],"
                         "sci[0-3],"
                         "lci[0-3],"
                         "pci[0-3],"
                         "iaqi[0-3],"
                         "ieqi[0-100]";
    char sensor_data[400];
    sprintf(sensor_data, "%s,"    // version
                         "%d,"    // unixtime
                         "%s,"    // time
                         "%d,"    // is_sleep[t/f]
                         "%d,"    // windowsensor_available[t/f]
                         "%d,"    // window_is_open[t/f]
                         "%d,"    // powersensor_available[t/f]
                         "%.2f,"  // powerADCValue[V]
                         "%.2f,"  // power[W]
                         "%.2f,"  // temperature[degC]
                         "%.2f,"  // humidity[%]
                         "%.2f,"  // pressure[hPa]
                         "%.2f,"  // radTemperature[degC]
                         "%d,"    // voci[0-500]
                         "%.1f,"  // light[lux]
                         "%.2f,"  // sound[-]
                         "%.2f,"  // wind_speed[m/s]
                         "%.2f,"  // co2[ppm]
                         "%.2f,"  // tci[0-3]
                         "%.2f,"  // sci[0-3]
                         "%.2f,"  // lci[0-3]
                         "%.2f,"  // pci[0-3]
                         "%.2f,"  // iaqi[0-3]
                         "%.2f",   // ieqi[0-100]
                         version,
                         time_now.unixtime(),
                         time_now_str,
                         isSleep,
                         WindowSensorisAvailable,
                         w_isOpen,
                         PowerSensorisAvailable,
                         powerADCValue,
                         power,
                         temperature,
                         humidity,
                         pressure,
                         radTemperature,
                         vocIndex,
                         light,
                         sound,
                         windSpeed,
                         co2,
                         TCI_val,
                         SCI_val,
                         LCI_val,
                         PCI_val,
                         IAQI_val,
                         IEQI_val
                         ); 
    
    if (!SD.exists(filename_data)){
      // create setting file and write the header if not exists
      sd_write(filename_data, data_header);
      debug_println("SD - data csv created!");
    }
    // append sensor data
    sd_append(filename_data, sensor_data);
  }
}
