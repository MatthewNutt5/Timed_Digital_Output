#include "Timed_Digital_Output.h"

#define PIN 2

Timed_Digital_Output tdo(PIN); // Constructor takes digital pin to output on

void setup() {
  tdo.init(); // Sets up pin as an output.

  // Sets period in microseconds.
  // set_period can optionally set duty cycle, defaults to 50%.
  // There is also set_frequency, which takes frequency in Hz.
  tdo.set_period(1000); 
  
  tdo.begin(); // Starts the first period.
}

void loop() {
  // Checks if enough time has elapsed to either put the pin LOW or
  // start the next period. Returns true if a new period was started
  // (pin goes HIGH) and false otherwise.
  // The more often you can call this function, the more accurate
  // the timing will be.
  tdo.poll();
}
