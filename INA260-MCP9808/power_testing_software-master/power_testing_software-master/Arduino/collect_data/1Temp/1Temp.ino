

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

// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
int incomingByte;      // a variable to read incoming serial data into

void setup() {
  Serial.begin(9600);
  // Wait until serial port is opened
  while (!Serial) { delay(10); }

  if (!tempsensor.begin(0x18)) {
    Serial.println("ERROR");
    while (1);
  }

  // init worked :) set up devices...
  tempsensor.setResolution(3); // mode: 3, resolution: 0.0625°C, sample Period: 250 ms
  tempsensor.wake(); // wake up, ready to read!
}

void loop() {
    if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
   
    if (incomingByte == 'T') {
      float current, voltage, power, temp;

      temp    = tempsensor.readTempC();   // degC
      
      // Report to the host computer...
       Serial.print(temp, 4); Serial.print("\n");
    }
    }
}
