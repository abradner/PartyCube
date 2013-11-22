/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <MinimalRemote.h>
#include "types.h"
#include "settings.h"
#include "colours.h"

const float lightLambda = 1.0/LIGHT_DECAY;

IRrecv irrecv(RECV_PIN);
decode_results results;
Colour r;
Colour g;
Colour b;

void setup()
{
#ifdef DEBUG
  Serial.begin(9600);
#endif
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    parse_colour(results.value);
    irrecv.resume(); // Receive the next value
  }
  decay_leds();
  
}
