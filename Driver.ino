//TODO inline function
void write_colour(int pin, int value) {
  Serial.println("Setting LED: (pin,val)");
  Serial.println(pin);
  Serial.println(value);
  analogWrite(pin,value);
}

