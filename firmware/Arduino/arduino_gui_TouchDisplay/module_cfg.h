#ifndef MODULE_CFG_H
#define MODULE_CFG_H

// module configuration

// ==== T/H/P: BME 280 ====
bool BME280isAvailable;                 // auto check in setup()

// ==== VOC: SGP40 ====
bool SGP40isAvailable;                  // auto check in setup()

// ==== light: VEML7700 ====
bool VEML7700isAvailable;               // auto check in setup()

// ==== CO2: SCD30 ====
bool SCD30isAvailable;                  // auto check in setup()

// ==== sound ====
bool SoundSensorisAvailable = true;     // Manual entry

// ==== wind speed====
bool WindSensorisAvailable = false;     // Manual entry

// ==== window sensor ====
bool WindowSensorisAvailable = false;   // Manual entry

// ==== power/current sensor ====
bool PowerSensorisAvailable = false;    // Manual entry
bool PowerSensorCurrentOutput = true;   // Manual entry, true if using power sensor with current signal output e.g. 0-50mA

// ==== T (DS18B20) for radiation temperature ====
bool RadTempSensorisAvailable = false;     // Manual entry

// ==== RFID ====
bool RFIDisAvailable = false;           // Manual entry

// ==== SD card module ====
bool SDisAvailable = true;              // Manual entry

#endif
