/*
*    Must import libraries from the following repositories:
*        https://github.com/adafruit/Adafruit_MCP9808_Library
*        https://github.com/adafruit/Adafruit_INA260
*/
/**
 * @file collect_data.ino
 * @author Andrew Rooney
 * @date 2020-07-09
 */

#include <Wire.h>
#include <Adafruit_INA260.h>
#include "Adafruit_MCP9808.h"
#include <ADC_Handler.h>
#include <common_defines.h>


// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
Adafruit_INA260 ina260_1    = Adafruit_INA260();
ADC_Handler handle = ADC_Handler();
int incomingByte;      // a variable to read incoming serial data into

void setup() {
  Serial.begin(9600);
  // Wait until serial port is opened
  while (!Serial) { delay(10); }

  if (!ina260_1.begin(0x41) || !tempsensor.begin(0x18)) {
    Serial.println("ERROR");
    while (1);
  }

  // init worked :) set up devices...
  ina260_1.setMode(INA260_MODE_CONTINUOUS);
  tempsensor.setResolution(3); // mode: 3, resolution: 0.0625°C, sample Period: 250 ms
  tempsensor.wake(); // wake up, ready to read!
}

void loop() {
    if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    // if it's a capital C (ASCII 72) print current:
    if (incomingByte == 'C') {
      float current, voltage, power, temp;
    
      current = ina260_1.readCurrent();     // mA
      
      // Report to the host computer...
         Serial.print(current, 4); Serial.print("\n");
    }
    if (incomingByte == 'V') {
      float current, voltage, power, temp;
    
      voltage = ina260_1.readBusVoltage();  // mV
      
      // Report to the host computer...
         Serial.print(voltage, 4); Serial.print("\n");
    }
    if (incomingByte == 'P') {
      float current, voltage, power, temp;
    
      power   = ina260_1.readPower();       // mW
      
      // Report to the host computer...
       Serial.print(power, 4); Serial.print("\n");
    }
    if (incomingByte == 'T') {
      float current, voltage, power, temp;

      temp    = tempsensor.readTempC();   // degC
      
      // Report to the host computer...
       Serial.print(temp, 4); Serial.print("\n");
    }
    }
}
