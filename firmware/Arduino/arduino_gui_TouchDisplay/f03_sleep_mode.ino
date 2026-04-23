// ==== Sleep Mode ====

// sleep mode will turn off nextion display and have a larger measurement interval to save energy
void sleep_mode() {
  // software debouncing to prevent "touch" issue if using an usb charger with noisy power supply or false button presses
  if(digitalRead(digitalPinSleepModeButton) != HIGH){
    lastDebounceTime = millis();  // reset the debounce timer
  }
  // use push button to switch isSleep status
  if(digitalRead(digitalPinSleepModeButton) == HIGH && (millis() - lastDebounceTime) > debounceDelay){
    switch_sleep_status();
  }
  if (mfrc522.PICC_IsNewCardPresent()) {
    rfid();
  }
}

void rfid() {
  // set an interval time for RFID to avoid switching sleep mode too fast
  if (millis() - previousMillis_rfid >= 3000) {
    previousMillis_rfid = millis();
    switch_sleep_status();
  }
}

void switch_sleep_status() {
  digitalWrite(digitalPinLED, HIGH); // turn on LED
  if(isSleep == false)
  {
    isSleep = true;
    updateInterval = updateIntervalSleep;
  }
  else 
  {
    isSleep = false;
    updateInterval = updateIntervalDefault;
  }
  // update sleep mode state to nextion display after switch
#ifdef DEBUG_MODE_IN_NEXTION_HMI
  Serial.print("is_sleep.val=");Serial.print(isSleep);Serial.write(0xff);Serial.write(0xff);Serial.write(0xff); // variable to store sleep state
  Serial.print("sleep=");Serial.print(isSleep);Serial.write(0xff);Serial.write(0xff);Serial.write(0xff); // tell nextion display the sleep state
#else
  Serial2.print("is_sleep.val=");Serial2.print(isSleep);Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff); // variable to store sleep state
  Serial2.print("sleep=");Serial2.print(isSleep);Serial2.write(0xff);Serial2.write(0xff);Serial2.write(0xff); // tell nextion display the sleep state
#endif
  delay(1000);
  digitalWrite(digitalPinLED, LOW);  // turn off LED
}
