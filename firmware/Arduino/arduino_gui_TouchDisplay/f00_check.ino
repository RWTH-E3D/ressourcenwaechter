// ==== Check hardware and initialization ====

void check_sd(){
  // SD card module 
  if (SDisAvailable) {
    if(!SD.begin(CS_PIN)){
      debug_println("SD card check: card mount failed!");
      SDisAvailable = false;
      delay(1500);
      debug_println("SD card check: try again...");
      delay(1500);
      if(!SD.begin(CS_PIN)){
        debug_println("SD card check: card mount second try failed!");
        SDisAvailable = false;
      }else{
        SDisAvailable = true;
      }
    }
  }
  // initialization
  if (SDisAvailable) {  
#ifdef DEBUG_MODE
    uint8_t cardType = SD.cardType();
    
    Serial.print("SD card check - card type: ");Serial.println(cardType);
    Serial.printf("SD card check - total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
    Serial.printf("SD card check - used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
#endif
  }
}

void check_rtc(){
  // RTC
  if (! rtc.begin()) {
    debug_println("RTC check: Failed to find RTC module, check wiring!");
#ifdef DEBUG_MODE_IN_NEXTION_HMI
    Serial.print("error_rtc.val=1");Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
    delay(5000);
    Serial.print("error_rtc.val=1");Serial.write(0xff);Serial.write(0xff);Serial.write(0xff);
#else
    Serial2.print("error_rtc.val=1");Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
    delay(5000);
    Serial2.print("error_rtc.val=1");Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff);
#endif
  }
#ifdef UPDATE_RTC
  rtc.adjust(DateTime(__DATE__, __TIME__));
  debug_println("RTC check: time updated!");
#endif
  debug_println("RTC check: setup done!");
}

void check_wiring(){

  // start bme280 sensor
  if (!bme.begin(I2C_BME280)) {
    Serial.println("Sensor check: Failed to find BME280 sensor, check wiring!");
    BME280isAvailable = false;
  } else {
    BME280isAvailable = true;
    debug_println("Sensor check: BME280 OK!");
  }
  
  // start SGP40 sensor
  if (!sgp.begin()){
    Serial.println("Sensor check: Failed to find SGP40 sensor, check wiring!");
    SGP40isAvailable = false;
  } else {
    SGP40isAvailable = true;
    debug_println("Sensor check: SGP40 OK!");
  }
  
  // start veml7700 sensor
  if (!veml.begin()) {
    Serial.println("Sensor check: Failed to find VEML7700 sensor, check wiring!");
    VEML7700isAvailable = false;
  } else {
    veml.setLowThreshold(10000);
    veml.setHighThreshold(20000);
    veml.interruptEnable(true);
    VEML7700isAvailable = true;
    debug_println("Sensor check: VEML7700 OK!");
  }
  
  // start scd30 sensor
  // Enable ASC only if enableSCD30ASC is true, it's disabled by default.
  if (!scd30.begin(Wire,enableSCD30ASC)) {
    Serial.println("Sensor check: Failed to find SCD30 sensor, check wiring!");
    SCD30isAvailable = false;
  } else {
    SCD30isAvailable = true;
    debug_println("Sensor check: SCD30 OK!");
    if (enableSCD30ASC){
      debug_println("SCD30: ASC enabled!");
    } else {
      debug_println("SCD30: ASC disabled!");
    }
  }

  // start DS18B20 via OneWire bus
  if (RadTempSensorisAvailable) {
    RadTempSensor.begin();  
  }

  // RFID MFRC522
  if (RFIDisAvailable) {
    mfrc522.PCD_Init();
    debug_println("RFID check: MFRC522 OK!"); 
  }

  // LED
  pinMode(digitalPinLED, OUTPUT);
  debug_println("LED check: setup done!");

  // reed switch
  if (WindowSensorisAvailable) {
    pinMode(digitalPinReedSwitch, INPUT);
    debug_println("Reed Switch check: setup done!");
  }
  
  // sleep mode
//  pinMode(digitalPinSleepModeButton, INPUT);
  pinMode(digitalPinSleepModeButton, INPUT_PULLDOWN);
  debug_println("Sleep Mode check: setup done!");

  
}
