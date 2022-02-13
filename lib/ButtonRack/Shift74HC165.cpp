#include "Shift74HC165.h"

#include <Arduino.h>

Shift74HC165::Shift74HC165(uint8_t shift_load_pin, uint8_t clock_pin,
                uint8_t serial_data_pin)
  : _shift_load_pin{shift_load_pin},
    _clock_pin{clock_pin},
    _serial_data_pin{serial_data_pin} {

    pinMode(_shift_load_pin, OUTPUT);
    pinMode(_clock_pin, OUTPUT);
    pinMode(_serial_data_pin, INPUT);
}

uint8_t Shift74HC165::shift_in(void) const {
    const uint8_t retries = 3;
    uint8_t current;
    uint8_t i;


    uint8_t result = this->_hardware_shift_in();

    for (i = 0; i < retries - 1; ++i) {
        current = this->_hardware_shift_in();
        if (current != result) {
            return 0;
        } 
        result = current;
        delay(100);
    }


    return result;
}

uint8_t Shift74HC165::_hardware_shift_in(void) const {

    uint8_t result = 0;

    // Prevent parallel data from changing during shift_in
    digitalWrite(_shift_load_pin, HIGH);
    
    result = shiftIn(_serial_data_pin, _clock_pin, MSBFIRST);

    // Allow parallel data to enter
    digitalWrite(_shift_load_pin, LOW);

    return result;
}
