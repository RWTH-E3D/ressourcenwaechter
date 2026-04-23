#ifndef PIN_CFG_H
#define PIN_CFG_H

// Pin configuration

// ==== T/H/P: BME 280 ====
#define I2C_BME280                    0x76   // I2C

// ==== VOC: SGP40 ====
#define I2C_SGP40                     0x59   // I2C, it has only one I2C addressdefault address hardcoded in Adafruit library (not used in setup)

// ==== light: VEML7700 ====
#define I2C_VEML7700                  0x10   // I2C, it has only one I2C addressdefault address hardcoded in Adafruit library (not used in setup)

// ==== CO2: SCD30 ====
#define I2C_SCD30                     0x61   // I2C, it has only one I2C addressdefault address hardcoded in Adafruit library (not used in setup)

// ==== sound: SEN 0232 ====
#define analogPinSoundSensor          34      // analog pin, this pin read the analog voltage from the sound level meter

// ==== wind speed: Modern Device WindSensor Rev. C ====
#define analogPinForRV                32      // analog pin
#define analogPinForTMP               33      // analog pin

// ==== window sensor (reed switch) ====
#define digitalPinReedSwitch          27      // digital pin for window sensor input

// ==== power/current sensor ====
#define analogPinPowerSensor          35      // analog pin

// ==== OneWire bus for radiation temperature sensor DS18B20 ====
#define ONE_WIRE_BUS                  15      // digital pin for OneWire bus

// ==== RFID / SD card ====
#define RST_PIN                       0       // RST
#define SS_PIN                        5       // SS

// ==== SD card ====
#define CS_PIN                        4       // CS

// ==== sleep mode ====
#define digitalPinLED                 25      // Pin for LED
#define digitalPinSleepModeButton     26      // Pin for sleep mode button

#endif
