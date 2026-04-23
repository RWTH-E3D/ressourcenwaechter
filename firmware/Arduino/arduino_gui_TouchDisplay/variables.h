#ifndef VARIABLES_H
#define VARIABLES_H

// Variables

// ==== Storage ====
const char filename_settings[] = "/setting.txt";
const char filename_userdata[] = "/usrdat.txt";
char userdata_default[] = "0;0;";  // format: level;exp;
unsigned int sdUsedPercentage;

// ==== level system ====
char lvExpArray[2][30];
unsigned int level = 0;   // current level, max: 999
unsigned int expNow = 0;  // current exp point, max: 400000
unsigned int expNext;     // exp to be reached for next level, max: 400000

unsigned int previousLevel = 0;   // buffer to store previous level
unsigned int previousExp = 0;     // buffer to store previous exp point


// ==== T/H/P: BME 280 ====
Adafruit_BME280 bme;  // I2C
float temperature;
float temperatureAdjustment = -2.0; // change this value after your calibration!
//float temperatureAdjustment = -3.47; // change this value after your calibration!
float humidity;
float humidityAdjustment = 5.9;    // change this value after your calibration!
//float humidityAdjustment = 6.9;    // change this value after your calibration!
float pressure;
float pressureAdjustment = 0.0;     // change this value after your calibration!

// ==== VOC: SGP40 ====
Adafruit_SGP40 sgp;   // I2C
uint16_t vocRaw;
int32_t vocIndex;


// ==== light: VEML7700 ====
Adafruit_VEML7700 veml = Adafruit_VEML7700(); // I2C
float light;
float lightRaw;
float lightAdjustment_A = 0.5870;    // change this value after your calibration!
float lightAdjustment_B = 139.6;    // change this value after your calibration!
//float lightAdjustment_A = 0.5373;    // change this value after your calibration!
//float lightAdjustment_B = 233.08;    // change this value after your calibration!


// ==== ADC setting for all analog sensors ====
#define VREF  3.3  // voltage on AREF pin, default:operating voltage
#define ADCrange  4095  // range for ADC, Arduino Nano has 10bit ADC (1024: 0-1023), ESP32 12bit (4096: 0-4095)


// ==== sound ====
float voltageValue;
float sound;
float soundAdjustment = -0.36;  // change this value after your calibration!
//float soundAdjustment = 14.14;  // change this value after your calibration!
int loop_sound = 10;  // loop times / sample times to read value from ADC for denoising


// ==== wind speed====
// to calibrate your sensor, put a glass over it, but the sensor should not be touching the desktop surface however.
// adjust the zeroWindAdjustment until your sensor reads about zero with the glass over it. 
const float zeroWindAdjustment = 0; // negative numbers yield smaller wind speeds and vice versa. Change this value after your calibration!
float TMP_Therm_ADunits;  //temp termistor value from wind sensor
float RV_Wind_ADunits;    //RV output from wind sensor 
float RV_Wind_Volts;
unsigned long lastMillis;
int TempCtimes100;
float zeroWind_ADunits;
float zeroWind_volts;
float windSpeed_MPH;
float windSpeed;
int loop_windspeed = 10; // loop times / sample times to read value from ADC for denoising


// ==== power/current sensor ====
int loop_power = 1000;  // loop times / sample times to read value from ADC for denoising
int powerVoltage = 230; // Volt
float powerADCValue;  // raw ADC value from current sensor for ampere value
double Irms;  // current Irms
double power;  // Watt (W) = Irms (A) * powerVoltage (V)
// variables to calculate Irms, from EmonLib.h
float SupplyVoltage = 3.3;
double ICAL = 100;  // calibration, theoretical value for 20 ohm sense resistor. See: https://docs.openenergymonitor.org/electricity-monitoring/ctac/calibration.html
//int sampleV;  //sample_ holds the raw analog read value
int sampleI;
//double lastFilteredV,filteredV; //Filtered_ is the raw analog value minus the DC offset
double filteredI;
//double offsetV = 12>>1; // Low-pass filter output, 12bit ADC, 10>>1 if 10bit
double offsetI = 12>>1; // Low-pass filter output, 12bit ADC, 10>>1 if 10bit
//double phaseShiftedV; // Holds the calibrated phase shifted voltage.
double sqV,sumV,sqI,sumI,instP,sumP;  //sq = squared, sum = Sum, inst = instantaneous
//int startV; //Instantaneous voltage at start of sample window.

//// may not needed
//int senseResistor = 20; // Ohms of sense resistor if using power sensor with current signal output. Won't do anything if PowerSensorCurrentOutput is false (power sensor with voltage signal output)
//int currentOutputRange = 50; // max current output (unit mA) from sensor (if its model with current signal output). If using model with voltage signal, it won't do anything.
//int voltageOutputRange = 1000; // max voltage output (unit mV) from sensor (if its model with voltage signal output). If using model with current signal, it won't do anything.
//int powerMeasurementRange = 100;  // measurement range of power sensor, unit Ampere (A).


// ==== CO2: SCD30 ====
SCD30 scd30;  // I2C
float co2;
/*
  Ff enable auto self-calibration mode of SCD30, default: false.
  To update the reference value saved in a non-volatile memory on the sensor device using ASC,
  the sensor needs to be continuously powered for at least 7 days, 
  with at least 1 hour of good ventilation (thereby obtaining the outdoor CO2 concentration) every day, 
  and set to an internal reference of 400 ppm. (Note: simplified, the actual outdoor concentration may be higher than 400 ppm).
  It is switched off by default because, based on our measurements, the factory-set FRC already has very good performance. 
  It can be considered to be switched on if long-term monitoring is planned in a well-ventilated building (> 6 months).
*/
bool enableSCD30ASC = false;


// ==== T: DS18B20 ====
OneWire oneWire(ONE_WIRE_BUS);  // OneWire communication
DallasTemperature RadTempSensor(&oneWire);  // Dallas DS18B20 for radiation temperature
float radTemperature;
float radTemperatureAdjustment = 0; // change this value after your calibration!

// ==== window sensor ====
bool w_isOpen;


// ==== RFID ====
MFRC522 mfrc522(SS_PIN, RST_PIN); // SPI


// ==== sleep mode ====
bool isSleep = false;  // default false
unsigned long lastDebounceTime = 0; // debounce timer
unsigned long debounceDelay = 50;  // [ms] debounce time in milliseconds

// ==== update ====
unsigned long previousMillis = 0; // store previous millis() for get sensor data
unsigned long previousMillis_rfid = 0; // store previous millis() for RFID
unsigned long previousMillis_output = 0; // store previous millis() for serial output
bool status_updated = false;
unsigned long updateInterval = 15000;  // [ms] update interval
unsigned long updateIntervalDefault = 15000;  // [ms], default value for setting interval after wake up from sleep mode, should be consistent with UpdateInterval above
unsigned long updateIntervalSleep = 60000;  // [ms], default value for setting interval after switching to sleep mode
unsigned int counter_sd = 0;  // counter for reading sd card usage info

// ==== RTC ====
char days[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
RTC_DS3231 rtc;
DateTime time_now;
char time_now_str[40];

// ==== predicted comfort ====
float met = 1.2;
float clo = 0.7;
// weights for each index, 0-1: not important, 1: default, 1-2: important, 2-3: very important
float TCI_weight = 2.0;
float SCI_weight = 1.5;
float LCI_weight = 1.0;
float PCI_weight = 0.5;
float IAQI_weight = 1.0;
// variables
float TCI_val;
float SCI_val;
float LCI_val;
float PCI_val;
float IAQI_val;
float IEQI_val;
float pressure_most_comfort_min = 950.0;
float pressure_most_comfort_max = 1050.0;
float pressure_comfort_min = 900.0;
float pressure_comfort_max = 1100.0;
float pressure_not_comfort_min = 800.0;
float pressure_not_comfort_max = 1200.0;
int voc_good_max = 80;
int voc_moderate_max = 120;
int voc_unhealthy_max = 200;
float co2_good_max = 950.0;
float co2_moderate_max = 1200.0;
float co2_unhealthy_max = 1750.0;
float light_most_comfort_min = 750.0;
float light_comfort_min = 300.0;
float light_not_comfort_min = 100.0;
float sound_most_comfort_max = 30.0;
float sound_comfort_max = 55.0;
float sound_not_comfort_max = 80.0;
float wind_speed_most_comfort_max = 0.12;
float wind_speed_comfort_max = 0.24;
float wind_speed_not_comfort_max = 0.9;



#endif
