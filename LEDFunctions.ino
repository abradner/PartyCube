
void zero_colour(Colour* col) {
  col->valNow;
  col->val0;
  col->t0; 
}

void decay_led(Colour* col, int t) {
  if (round(col->valNow) == 0) { 
    zero_colour(col);
    return;
  };
  
  float newVal = (exp_decay(col->val0, lightLambda, dt(t,col->t0)));
  
  // Update LED and colour object
  if (col->valNow != newVal) {  
    write_colour(col->pin, newVal);
#ifdef DEBUG
    Serial.print("LED Decay from ");
    Serial.print(col->valNow);
    Serial.print(" to ");
    Serial.print(newVal);
    Serial.print(" @ ");
    Serial.print(t);
    Serial.print(" (Initially ");
    Serial.print(col->val0);
    Serial.print(" @ ");
    Serial.print(col->t0);
    Serial.println(")");
#endif    
  }
  col->valNow = newVal; 
}

void decay_leds() {
  int t=millis();
  decay_led(&r,t);
  decay_led(&g,t);
  decay_led(&b,t);
}


void update_colour (Colour* col, int newVal) {
  //Add our new pulse of light to any existing light there was (capping at 255)
  //This will mean that old, lingering colours might decay a little strangely,
  // but that shouldn't be noticable
  int combinedPower = min(col->valNow + newVal, MAX_BRIGHTNESS);

  // Now update the colour
  col->valNow = combinedPower;
  col->val0 = combinedPower;
  col->t0 = millis();

  write_colour(col->pin, newVal);

  //And update the LED for t[0]
#ifdef DEBUG
  Serial.print ("Updating LED: ");
  Serial.print(col->pin);
  Serial.print(" to ");
  Serial.print(col->valNow);
  Serial.print(" @ ");
  Serial.println(col->t0);
#endif    
}

void paint_led (float newR, float newG, float newB) {
#ifdef DEBUG
  Serial.print("Painting Colours: (RGB)(");
  Serial.print(newR);
  Serial.print(",");
  Serial.print(newG);
  Serial.print(",");
  Serial.print(newB);
  Serial.println(")");
#endif      
  update_colour(&r,newR);
  update_colour(&g,newG);
  update_colour(&b,newB);  
}


