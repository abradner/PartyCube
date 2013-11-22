// Exponential decay, using x(t) = x[0]*e^(-λt)
// x(t) is the brightness at some after t[0]
// x[0] is the initial value of x at t[0]
// λ is the decay rate
// t is the current time after t[0]
float exp_decay(float x0, float lambda, int t){
  return (x0 * exp(-1*lambda*t));
}

//TODO inline function
int t(int t0) {
  millis() - t0;  
}
