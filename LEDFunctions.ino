//TODO inline function
void write_colour(int pin, int value) {
  Serial.println("Setting LED: (pin,val)");
  Serial.println(pin);
  Serial.println(value);
  analogWrite(pin,value);
}

void decay_led(Colour* col, int t=0) {
//  float newVal = (t==0) ? col->val0 :   exp_decay(col->val0, lightLambda, t);
  if (col->valNow == 0) { return; };
  float newVal = exp_decay(col->val0, lightLambda, t);
  if (newVal < 0.5) { newVal = 0;}

  // Update LED and colour object
  if (round(col->valNow) != round(newVal)) {  
    write_colour(col->pin, newVal);
    #ifdef DEBUG
      Serial.println("LED Decay: (valNow,val0,t0, newVal)");
      Serial.println(col->valNow);
      Serial.println(col->val0);
      Serial.println(col->t0);
      Serial.println(newVal);
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
  
  //And update the LED for t[0]
  #ifdef DEBUG
    Serial.println("Initial Decay: (valNow,val0,t0)");
    Serial.println(col->valNow);
    Serial.println(col->val0);
    Serial.println(col->t0);
  #endif    
  decay_led(col, col->t0);
}

void paint_led (float newR, float newG, float newB) {
  #ifdef DEBUG
    Serial.println("Painting LED: ");
    Serial.println(newR);
    Serial.println(newG);
    Serial.println(newB);
  #endif      
  update_colour(&r,newR);
  update_colour(&g,newG);
  update_colour(&b,newB);  
}

