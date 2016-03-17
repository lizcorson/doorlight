/* doorlight
 * Turns an LED strip on when a magnetic door sensor is triggered by a door opening.
 * Turns off after 60 seconds.
 * Thanks to this tutorial: https://learn.adafruit.com/using-ifttt-with-adafruit-io/overview
 * 
 * Liz Corson
 * 16 March 2016
 */

#include "FastLED.h"

#define DOOR 13 // door sensor is on pin 13
#define NUM_LEDS 30
#define DATA_PIN 6 // LED strip on pin 6

const int doorCheckDelay = 500;
long lastDoorCheck = 0;
long lightsOnWait = 60000; //60 seconds
long lightsOnTime = 0;
byte lightsOn = 0;

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
  	  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
      pinMode(DOOR, INPUT_PULLUP);
      Serial.begin(9600);
      LEDsOff();
}

void loop() { 
  if ((unsigned long)(millis() - lastDoorCheck) > doorCheckDelay) {
    // if door isn't open, we don't need to send anything
    if(digitalRead(DOOR) == LOW) {
      Serial.println("Door closed");
      // we don't do anything
    } else {
      // the door is open if we have reached here,
      // so we should turn LEDs on
      Serial.println("Door is open!");
      if (lightsOn == 0) {
        LEDsOn();
        lightsOn = 1;
        lightsOnTime = millis();
        Serial.println("Lights turned on");
      }
    }
    if (lightsOn == 1) {
        int ontime = (unsigned long)(millis() - lightsOnTime)/1000;
        Serial.print("Lights on for ");
        Serial.print(ontime);
        Serial.println(" s");
      }
    lastDoorCheck = millis();
  }
  
  if ((unsigned long)(millis() - lightsOnTime) > lightsOnWait && lightsOn == 1) {
    lightsOn = 0;
    LEDsOff();
  }
 
}

void LEDsOn() {
    for(int i = 0; i < NUM_LEDS; i++ ){
      leds[i].setRGB(255,0,0);  // setRGB functions works by setting
                             // (RED value 0-255, GREEN value 0-255, BLUE value 0-255)
                             // RED = setRGB(255,0,0)
                             // GREEN = setRGB(0,255,0)
      FastLED.show();
  }
}

void LEDsOff() {
  for(int i = 0; i < NUM_LEDS; i++ ){
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}
