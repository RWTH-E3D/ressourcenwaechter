// ==== Utilities ====

void debug_println(char debug_info[]) {
#ifdef DEBUG_MODE
  Serial.println(debug_info);
  delay(200);
#endif
}

// SD card
void sd_write(const char *path, char *message){
  // add LED indication to avoid turning off during writing
  digitalWrite(digitalPinLED, HIGH); // turn on LED
  delay(400);
#ifdef DEBUG_MODE  
  Serial.printf("SD - Writing file: %s\n", path);
#endif
  File file = SD.open(path, FILE_WRITE);
  if(!file){
    debug_println("SD - Error: failed to open file for writing!");
    return;
  }
  if(file.println(message)){
    debug_println("SD - File written successful!");
  } else {
    debug_println("SD - Error: failed to write following data!");
    debug_println("----------");
    debug_println(message);
    debug_println("----------");
  }
  file.close();
  delay(100);
  digitalWrite(digitalPinLED, LOW);  // turn off LED
}

void sd_append(const char * path, char * message){
  // add LED indication to avoid turning off during writing
  digitalWrite(digitalPinLED, HIGH); // turn on LED
  delay(250);
#ifdef DEBUG_MODE   
  Serial.printf("SD - Appending to file: %s\n", path);
#endif
  File file = SD.open(path, FILE_APPEND);
  if(!file){
    debug_println("SD - Error: failed to open file for appending!");
    return;
  }
  if(file.println(message)){
    debug_println("SD - File appended successful!");
  } else {
    debug_println("SD - Error: failed to append following data!");
    debug_println("----------");
    debug_println(message);
    debug_println("----------");
  }
  file.close();
  delay(250);
  digitalWrite(digitalPinLED, LOW);  // turn off LED
}
