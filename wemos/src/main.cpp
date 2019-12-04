using namespace std;

#include <Wire.h>
#include <Arduino.h>
#include <string>
#include <Adafruit_NeoPixel.h>
#include "domobjects/domobject.h"
#include "components.h"
#include "wifiHandler.h"

/// Get the right configuration (Decided at compile-time)
#ifdef BED
Bed object;
#endif

#ifdef CHAIR
Chair object;
#endif



Adafruit_NeoPixel led(1, D5, NEO_GRB + NEO_KHZ800);


void setup() {
    Serial.begin(9600);
    delay(1000);
    wifiSetup();
    Serial.println("Hi, my name is " + object.getName());

    Wire.begin();

    // Config maxi 16647 (analog part)
    Wire.beginTransmission(0x36);
    Wire.write(byte(0xA2));
    Wire.write(byte(0x03));
    Wire.endTransmission();

    // Config 
    Wire.beginTransmission(0x38);
    Wire.write(byte(0x03));
    Wire.write(byte(0x0F));
    Wire.endTransmission();

    led.begin();
    led.show();
    led.setBrightness(255);

}

void loop() {
    handleWifi(&object);
    delay(20);
    componentCheckLoop();

      //led.show();
   led.setPixelColor(0, 255, 255, 255);
   led.show();


   Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);   
  unsigned int inputs = Wire.read();  
  Serial.print("Digital in: ");
  Serial.println(inputs&0x0F);  

  delay(500);
}

