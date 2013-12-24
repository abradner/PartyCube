/*
 * PartyCube: 
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <MinimalRemote.h>
#include "types.h"
#include "settings.h"
#include "colours.h"

const float lightLambda = 1.0/(float)LIGHT_DECAY;

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
  r.pin = R_PIN;
  g.pin = G_PIN;
  b.pin = B_PIN;

zero_colour(&r);
zero_colour(&g);
zero_colour(&b);

update_colour(&r, 255);
update_colour(&b, 255);
update_colour(&g, 255);

  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
  #ifdef DEBUG
    Serial.println("Received Command");
  #endif    
    parse_colour(results.value);
    irrecv.resume(); // Receive the next value
  #ifdef DEBUG
    Serial.println("");
  #endif    
  }
  decay_leds();
}
