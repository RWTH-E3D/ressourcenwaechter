/*
  Comparison of Modern Device Wind Sensor Rev. P and C
  Author: Qirui Huang
  
  Email: qirui.huang@e3d.rwth-aachen.de
  MCU: ESP-32 Dev Kit C V4
  
  License: GNU GPL-3.0
*/
// ==== Sensor pins ====
#define analogPinRVRevC    34   // RV pin for Rev. C
#define analogPinTMPRevC   35   // TMP pin for Rev. C
#define analogPinRVRevP    32   // RV/OUT pin for Rev. C
#define analogPinTMPRevP   33   // TMP pin for Rev. P

// ==== ADC setting for all analog sensors ====
#define VREF  3.3  // voltage on AREF pin, default:operating voltage
#define ADCrange  4095  // range for ADC, Arduino Nano has 10bit ADC (1024: 0-1023), ESP32 12bit (4096: 0-4095)

// ==== Calibration ====
// to calibrate the sensor, put a glass over it, but the sensor should not be
// touching the glass/desktop surface however.
// adjust the zeroWindAdjustment until your sensor reads about zero with the glass over it. 
const float zeroWindAdjustment_RevC_method1 = -2.55;
const float zeroWindAdjustment_RevC_method2 = -2.55;
const float zeroWindAdjustment_RevC_method3 = 1.0;
// no adjustment for method 4
const float zeroWind_V_RevP_method5 = 0.98;

// ==== Constants (method 3) ====
const float K1 = 15.36921;
const float K2 = 0.01788;
const float K3 = -29.04560;
const float K4 = 1.01536;
const float T_rev_c = 21.9;

// ==== Libraries ====
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;
 
// ==== Variables ====
// raw value Rev C
float TMP_Therm_ADunits_RevC;
float RV_Wind_ADunits_RevC;
float RV_Wind_Volts_RevC;
// raw value Rev P
float TMP_Therm_ADunits_RevP;
float RV_Wind_ADunits_RevP;
float RV_Wind_Volts_RevP;
// method 1
float TempCtimes100;
float zeroWind_ADunits;
float zeroWind_volts_method1;
float WindSpeed_MPH_RevC_1;
float WindSpeed_RevC_1;
// method 2
float A;
float zeroWind_volts_method2;
float WindSpeed_MPH_RevC_2;
float WindSpeed_RevC_2;
// method 3
float RV_Wind_ADunits_RevC_1000;
float TempBME;
float WindSpeed_RevC_3;
// method 4
float WindSpeed_MPH_RevP_4;
float WindSpeed_RevP_4;
// method 5
float tempC_RevP;
float WindSpeed_MPH_RevP_5;
float WindSpeed_RevP_5;
// time
unsigned long lastMillis;


void setup() {
  Serial.begin(9600);
  Serial.println("start");
  //initialize BME280
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  if (millis() - lastMillis > 2000){      // read every 2000 ms - printing slows this down further
    
    // reading air temperature
    TempBME = bme.readTemperature();      // temperature value from sensor BME280
    Serial.print("TempBME degC;");
    Serial.print(TempBME);
    Serial.print(";");
    
    // reading analog values from wind sensors
    // averaging sampling for denoising
    // Rev. C
    RV_Wind_ADunits_RevC = analogRead(analogPinRVRevC);     // 1st reading
    TMP_Therm_ADunits_RevC = analogRead(analogPinTMPRevC);  // 1st reading
    for (int i=0; i<9; i++){                                // 9 additional readings
      RV_Wind_ADunits_RevC += analogRead(analogPinRVRevC);
      TMP_Therm_ADunits_RevC += analogRead(analogPinTMPRevC);
    } 
    RV_Wind_ADunits_RevC /=10;                              // average
    TMP_Therm_ADunits_RevC /=10;                            // average
    Serial.print("RV_Wind_ADunits_RevC;");
    Serial.print(RV_Wind_ADunits_RevC);
    Serial.print(";");
    Serial.print("TMP_Therm_ADunits_RevC;");
    Serial.print(TMP_Therm_ADunits_RevC);
    Serial.print(";");
    
    RV_Wind_Volts_RevC = (RV_Wind_ADunits_RevC * VREF / ADCrange);
    Serial.print("RV_Wind_Volts_RevC;");
    Serial.print(RV_Wind_Volts_RevC);
    Serial.print(";");
    

    // Rev. P
    RV_Wind_ADunits_RevP = analogRead(analogPinRVRevP);     // 1st reading
    TMP_Therm_ADunits_RevP = analogRead(analogPinTMPRevP);  // 1st reading
    for (int i=0; i<9; i++){                                // 9 additional readings
      RV_Wind_ADunits_RevP += analogRead(analogPinRVRevP);
      TMP_Therm_ADunits_RevP += analogRead(analogPinTMPRevP);
    }
    RV_Wind_ADunits_RevP /=10;                              // average
    TMP_Therm_ADunits_RevP /=10;                            // average
    Serial.print("RV_Wind_ADunits_RevP;");
    Serial.print(RV_Wind_ADunits_RevP);
    Serial.print(";");
    Serial.print("TMP_Therm_ADunits_RevP;");
    Serial.print(TMP_Therm_ADunits_RevP);
    Serial.print(";");
    
    RV_Wind_Volts_RevP = (RV_Wind_ADunits_RevP * VREF / ADCrange);
    Serial.print("RV_Wind_Volts_RevP;");
    Serial.print(RV_Wind_Volts_RevP);
    Serial.print(";");
    
    
    /* -------------- Method 1 --------------
     * Regression function provided by the manufacturer
     * https://github.com/moderndevice/Wind_Sensor
     * -------------------------------------- */
    TempCtimes100 = (0.005 *(TMP_Therm_ADunits_RevC * TMP_Therm_ADunits_RevC)) - (16.862 * TMP_Therm_ADunits_RevC) + 9075.4;  // Temperature in C times 100
    
    zeroWind_ADunits = -0.0006 *(TMP_Therm_ADunits_RevC * TMP_Therm_ADunits_RevC) + 1.0727 * TMP_Therm_ADunits_RevC + 47.172;  // 13.0C  553  482.39
    
    zeroWind_volts_method1 = (zeroWind_ADunits * VREF/ADCrange) - zeroWindAdjustment_RevC_method1;  // VREF / ADCrange instead of 0.0048828125, in our case it's 3.3 / 4095 (12-bit ADC, 3.3V ESP32)
    Serial.print("zeroWind_volts Rev C Method 1;");
    Serial.print(zeroWind_volts_method1);
    Serial.print(";");
    
    WindSpeed_MPH_RevC_1 =  pow(((RV_Wind_Volts_RevC - zeroWind_volts_method1) /.2300) , 2.7265);  
    WindSpeed_RevC_1 = WindSpeed_MPH_RevC_1 * 0.44704; // mph -> m/s
    Serial.print("WindSpeed m/s Rev C Method 1;");
    Serial.print(WindSpeed_RevC_1);
    Serial.print(";");
    
    /* -------------- Method 2 --------------
     * slightly modified formula from doi:10.3390/s150613012
     * only changing the power (A) of the first formula (2.7265, see above)
     * -------------------------------------- */
    A = -4.089 * pow(RV_Wind_Volts_RevC, 2) + 22.697 * RV_Wind_Volts_RevC - 29.371;
    zeroWind_volts_method2 = (zeroWind_ADunits * VREF / ADCrange) - zeroWindAdjustment_RevC_method2;
    Serial.print("zeroWind_volts Rev C Method 2;");
    Serial.print(zeroWind_volts_method2);
    Serial.print(";");

    float baseValue = (RV_Wind_Volts_RevC - zeroWind_volts_method2) / 0.2300;
    WindSpeed_MPH_RevC_2 =  pow(baseValue, A);
    WindSpeed_RevC_2 = WindSpeed_MPH_RevC_2 * 0.44704;
    Serial.print("WindSpeed m/s Rev C Method 2;");
    Serial.print(WindSpeed_RevC_2);
    Serial.print(";");
      
    /* -------------- Method 3 --------------
     * New regression function from doi:10.1016/j.indenv.2024.100048
     * Temperature is introduced as a correction factor, 
     * so additional temperature data is required, for example from the BME280.
     * -------------------------------------- */
    RV_Wind_ADunits_RevC_1000 = RV_Wind_ADunits_RevC / 1000; //correcting the error by dividing by 1000
    WindSpeed_RevC_3 = (2.285 * (pow(RV_Wind_ADunits_RevC_1000, 3))- 12.417 * (pow(RV_Wind_ADunits_RevC_1000, 2)) + 22.831 * RV_Wind_ADunits_RevC_1000 - 14.19)/(K4 - (T_rev_c-TempBME) * K1 * pow(RV_Wind_ADunits_RevC_1000, K3) - (T_rev_c - TempBME) * K2) - zeroWindAdjustment_RevC_method3;  //new formula
    Serial.print("WindSpeed m/s Rev C Method 3;");
    Serial.print(WindSpeed_RevC_3);
    Serial.print(";");

    /* -------------- Method 4 --------------
     * Important: For Wind Sensor Rev. P (with 12V power supply, e.g. with step-up voltage converter)!
     * From Wind Sensor Rev P Arduino sketch provided by the manufacturer
     * https://moderndevice.com/products/wind-sensor-rev-p
     * Do not use this if using ESP32 since it's 12bit ADC
     * -------------------------------------- */
    // wind formula derived from a wind tunnel data, annemometer and some fancy Excel regressions
    // this scalin doesn't have any temperature correction in it yet
    WindSpeed_MPH_RevP_4 =  pow(((RV_Wind_ADunits_RevP - 264) / 85.6814), 3.36814); // no temperature correction
    WindSpeed_RevP_4 = WindSpeed_MPH_RevP_4 * 0.44704;  // mph -> m/s
    Serial.print("WindSpeed m/s Rev C Method 4;");
    Serial.print(WindSpeed_RevP_4);
    Serial.print(";");
    
    /* -------------- Method 5 --------------
     * Important: For Wind Sensor Rev. P (with 12V power supply, e.g. with step-up voltage converter)!
     * Regression function provided by the manufacturer
     * https://moderndevice.com/blogs/documentation/calibrating-the-rev-p-wind-sensor-from-a-new-regression
     * -------------------------------------- */
    tempC_RevP = ((TMP_Therm_ADunits_RevP * VREF / ADCrange) - 0.400) / .0195; // VREF & ADCrange instead of 5.0 & 1023 due to 12-bit ADC and 3.3V (ESP32)
    Serial.print("tempC_RevP Method 5;");
    Serial.print(tempC_RevP);
    Serial.print(";");
    
    WindSpeed_MPH_RevP_5 = pow(((((RV_Wind_ADunits_RevP * VREF / ADCrange) - zeroWind_V_RevP_method5) / (3.038517 * pow(tempC_RevP, 0.115157 ))) / 0.087288 ), 3.009364);
    WindSpeed_RevP_5 = WindSpeed_MPH_RevP_5 * 0.44704;  // mph -> m/s
    Serial.print("WindSpeed m/s Rev P Method 5;"); 
    Serial.print(WindSpeed_RevP_5);
    Serial.println(";");
    
    
    lastMillis = millis();
  }
} 

 
  
