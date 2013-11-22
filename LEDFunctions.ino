//TODO inline function
void write_colour(int pin, int value) {
  analogWrite(pin,value);
}

void decay_led(Colour* col, int t=0) {
  float newVal = (t==0) ? col->val0 :   exp_decay(col->val0, lightLambda, t);
  write_colour(col->pin, newVal);
}

void decay_leds() {
  decay_led(&r);
  decay_led(&g);
  decay_led(&b);
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
  decay_led(col, 0);
}

void paint_led (float newR, float newG, float newB) {
  update_colour(&r,newR);
  update_colour(&g,newG);
  update_colour(&b,newB);  
}

