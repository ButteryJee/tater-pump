/*************************************************** 
  This is an example for the SHT31-D Humidity & Temp Sensor

  Designed specifically to work with the SHT31-D sensor from Adafruit
  ----> https://www.adafruit.com/products/2857

  These sensors use I2C to communicate, 2 pins are required to  
  interface
 ****************************************************/
 
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"

bool enableHeater = false;
String cmd;

Adafruit_SHT31 sht31 = Adafruit_SHT31();

void setup() {
  Serial.begin(9600);

  while (!Serial)
    delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("boot");
  if (! sht31.begin(0x45)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }

  sht31.heater(false); // disable the heater during normal operation
}


void loop() {
  while(!Serial.available());
  cmd = Serial.readStringUntil('\n');
  cmd.trim();
  if (cmd.equals("temp_humid")) {
    writeTempHumiditySerial();
  }
  else {
    Serial.println("Command Invalid");
  }
}

void writeTempHumiditySerial() {
  float t = 0.0;
  float h = 0.0;
  getTempHumidity(&t, &h);

  if (! isnan(t)) {  // check if 'is not a number'
    Serial.print(t); 
    Serial.print(",");
  }
  else { 
    Serial.println("Failed to read temperature");
  }
  
  if (! isnan(h)) {  // check if 'is not a number'
    Serial.println(h);
  } else { 
    Serial.println("Failed to read humidity");
  }
}

void getTempHumidity(float* t, float* h) {
  *t = sht31.readTemperature()*1.8 + 32;
  *h = sht31.readHumidity();
}