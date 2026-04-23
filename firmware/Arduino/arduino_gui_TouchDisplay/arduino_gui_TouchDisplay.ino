// ==== Main Sketch ====

/*
  Ressourcenwächter Technische Hochschule
  Author: Qirui Huang
  Institute of Energy Efficiency and Sustainable Building (E3D)
  RWTH Aachen University
  
  Wiki of Ressourcenwächter: https://rw.e3d.rwth-aachen.de/
  
  Email: qirui.huang@e3d.rwth-aachen.de
  MCU: ESP-32 Dev Kit C V4
  
  License: GNU GPL-3.0
*/

// Debug Mode (Only one of the both debug mode can be enabled)
#define DEBUG_MODE  // In debug mode, more relevant info will be printed on the serial port. Comment this line if you don't need to check debug info in serial monitor. 
//#define DEBUG_MODE_IN_NEXTION_HMI // Debug mode to transfer data for Nextion touch display via serial 0 (USB) to debug in HMI software. Comment this line after finishing debugging. 

/*-
  Update RTC time to the time the code was compiled. 
  It is best to keep the device on winter time. 
  If it is on summer time, there will be an overlap of one hour when the time is switched. 
  If it's on winter time, there will be a one-hour gap but it will be easier to identify.
*/
//#define UPDATE_RTC  // Comment this line if you don't need to update the time. 

// Version
char version[] = "1.2.2";

/* 
  Libraries
  check requirements.txt or info below to install required libraries
  - Adafruit BME280 Library by Adafruit (version 2.2.2)
  - Adafruit SGP40 by Adafruit (version 1.1.3)
  - Adafruit VEML7700 by Adafruit (version 2.1.6)
  - SparkFun SCD30 Arduino Library by SparkFun Electronics (version 1.0.20)
  - Adafruit Unified Sensor by Adafruit (version 1.1.6 or above)
  - OneWire by Paul Stoffregen (version 2.3.7)
  - DallasTemperature by Miles Burton (version 3.9.0)
  - MFRC522 by GithubCommunity (version 1.4.11)
  - RTClib by Adafruit (version 2.1.1)
  - SD Built-In by Arduino (version 1.2.4)
*/

// allows to communicate with I2C / TWI devices
#include <Wire.h>
// allows to communicate with SPI devices
#include <SPI.h>
// sensors
#include <Adafruit_Sensor.h>  // general libAdafruit sensor
#include "Adafruit_BME280.h"  // T/H/P: BME 280, v2.2.2
#include "Adafruit_SGP40.h" // VOC: SGP40, v1.1.3
#include "Adafruit_VEML7700.h"  // light: VEML7700, v2.1.6
#include "SparkFun_SCD30_Arduino_Library.h" // CO2: SCD30, v1.0.20
#include <OneWire.h>  // OneWire for DS18B20, v2.3.7
#include <DallasTemperature.h>  // T: DS18B20, v3.9.0
// RFID
#include <MFRC522.h>  // RFID, v1.4.11
// RTC
#include "RTClib.h" // RTC, v2.1.1
// SD card
#include "FS.h" // File system
#include "SD.h" // SD card, v1.2.4

// Settings
#include "module_cfg.h"  // configuration for module settings
#include "pin_cfg.h"  // configuration for hardware pins
#include "variables.h"  // variables and calibration offsets


void setup() {
  delay(1000);
  // start serial port
  Serial.begin(115200);
  debug_println("===== Debug Mode =====");
  debug_println("serial 0 started");
  delay(500);
  
  Serial2.begin(9600);  // Important: connect GND of Nextion display to GND of ESP32 (Common ground) while using external power supply for Nextion display!
  debug_println("serial 2 started");
  delay(500);

  SPI.begin();      // Init SPI bus
  delay(500);
  
  check_wiring();   // check component wiring
  delay(500);
  
  check_rtc();      // check Real Time Clock
  delay(500);
  
  check_sd();       // check SD card module
  delay(1000);
  
  save_settings();  // save system settings and check user data
  delay(1000);

  debug_println("===== Setup done! =====");
}

void loop() {
  get_data();           // get sensor data
  
  predicted_comfort();  // comfort and level system, disabled in sleep mode
  
  output();             // output data to serial 0/2 and save to sd
  
  sleep_mode();         // sleep mode
}
