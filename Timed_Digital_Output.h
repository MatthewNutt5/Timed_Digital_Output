/*
 * Timed_Digital_Output - Arduino class for toggling a digital output pin at a
 * set frequency/period and duty cycle, using the micros() function for timing.
 * Requires constant polling by loop() to operate. Quite naive.
 */

#ifndef TIMED_DIGITAL_OUTPUT
#define TIMED_DIGITAL_OUTPUT

#include <Arduino.h>

class Timed_Digital_Output {
    public:
        Timed_Digital_Output(unsigned char pin);
        void init();
        void begin();
        bool poll();
        void set_period(int period, float duty = NULL);
        void set_frequency(float frequency, float duty = NULL);
    private:
        bool _is_high;                  // Is the current period already low?
        unsigned char _pin;             // Pin to output on
        unsigned int _period;           // Period of oscillation
        unsigned int _high_period;      // Ditto, for digital high
        float _duty = 50.0f;            // Duty cycle, as a percentage
        unsigned long int _period_start;// Micros time the current period began
};

#endif