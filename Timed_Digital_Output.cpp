/*
 * Timed_Digital_Output - Arduino class for toggling a digital output pin at a set
 * frequency/period and duty cycle, using the micros() function for timing.
 * Requires constant polling by loop() to operate. Quite naive.
 */

#include <Arduino.h>
#include "Timed_Digital_Output.h"



/* Class constructor. */
Timed_Digital_Output::Timed_Digital_Output(unsigned char pin) {
    _pin = pin;
    return;
}



/* Initialization routine. */
void Timed_Digital_Output::init() {
    pinMode(_pin, OUTPUT);
    return;
}



/* Public functions. */
// Starts the first period - essentially a forced trigger.
void Timed_Digital_Output::begin() {
    digitalWrite(_pin, HIGH);
    _is_high = true;
    _period_start = micros();
    return;
}

// Checks if the period has elapsed - starts the next period if so.
bool Timed_Digital_Output::poll() {
    unsigned long int delta_micros = micros() - _period_start;
    if (delta_micros >= _period) {
        digitalWrite(_pin, HIGH);
        _is_high = true;
        _period_start += delta_micros;
        return true;
    } else if (_is_high && delta_micros >= _high_period) {
        digitalWrite(_pin, LOW);
        _is_high = false;
        return false;
    } else {
        return false;
    }
}

// Sets new period values, using the period as the input.
void Timed_Digital_Output::set_period(int period, float duty=NULL) {
    if (duty) {
        _duty = duty;
    }
    _period = period;
    _high_period = static_cast<int>((_period * _duty) / 100.0f);
    return;
}

// Sets new period values, using the frequency as the input.
void Timed_Digital_Output::set_frequency(float frequency, float duty=NULL) {
    if (duty) {
        _duty = duty;
    }
    _period = static_cast<int>((1.0f / frequency) * 1000000.0f);
    _high_period = static_cast<int>((_period * _duty) / 100.0f);
    return;
}