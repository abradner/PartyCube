/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <MinimalRemote.h>
#include "colours.h"

int RECV_PIN = 11;

const int rPin = 2; // the pin that the LED is attached to
const int gPin = 3; // the pin that the LED is attached to
const int bPin = 4; // the pin that the LED is attached to

const int fadeTime = 100;
const int lightLife = 2000;
const int fadeSteps = 10;

int rOld, gOld, bOld = 0;

int lightTime = 0;

IRrecv irrecv(RECV_PIN);

decode_results results;

void paint_led (float r, float g, float b) {
  
  int stepLength = (float)fadeTime / (float)fadeSteps;
    
  float rFinal = r/6;
  float gFinal = g/6;
  float bFinal = b/6;
  
  float rStep = (r-rFinal) / (float)fadeSteps;
  float gStep = (g-gFinal) / (float)fadeSteps;
  float bStep = (b-bFinal) / (float)fadeSteps;

#ifdef DEBUG
  Serial.print("stepLength: ");
  Serial.print(stepLength);
  Serial.print(" rFinal: ");
  Serial.print(rFinal);
  Serial.print(" rStep: ");
  Serial.print(rStep);
  Serial.println("");
#endif
  
  for (int i = 0; i < fadeSteps; i++) {
    
    int rOut = (int)(rOld-i*rStep);
    int gOut = (int)(gOld-i*gStep);
    int bOut = (int)(bOld-i*bStep);
#ifdef DEBUG
    Serial.print("i: ");
    Serial.print(i);
    Serial.print(" rOut: ");
    Serial.print(rOut);
    Serial.println("");
#endif
    analogWrite(rPin, rOut);
    analogWrite(gPin, gOut);
    analogWrite(bPin, bOut);
    delay (stepLength);
  }

  lightTime = millis();
  rOld = rFinal;
  gOld = gFinal;
  bOld = bFinal;
  analogWrite(rPin, rFinal);
  analogWrite(gPin, gFinal);
  analogWrite(bPin, bFinal);
  
}

void kill_light() {
  lightTime = 0;
  analogWrite(rPin, 0);
  analogWrite(gPin, 0);
  analogWrite(bPin, 0);
  rOld = 0;
  gOld = 0;
  bOld = 0;

}

void set_colour(int code) {
   switch (code) {
     case WHITE:
       paint_led(255,255,255);
       break;
     case RED:
       paint_led(255,0,0);
       break;
     case GREEN:
       paint_led(0,255,0);
       break;
     case BLUE:
       paint_led(0,0,255);
       break;
     case CYAN:
       paint_led(0,255,255);
       break;
     case YELLOW:
       paint_led(255,255,0);
       break;
     case MAGENTA:
       paint_led(255,0,255);
       break;
     default:
       break;
   }
}

void setup()
{
#ifdef DEBUG
  Serial.begin(9600);
#endif
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);

  irrecv.enableIRIn(); // Start the receiver
  
}

void loop() {
  if (irrecv.decode(&results)) {
    set_colour(results.value);
    irrecv.resume(); // Receive the next value
  }
  
  if ((lightTime != 0) && (millis() - lightTime >= lightLife)) {
    kill_light();
  }
}
