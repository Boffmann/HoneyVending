#include "Hardware/Shift74HC165.h"

#include <Arduino.h>

Shift74HC165::Shift74HC165(uint8_t shift_load_pin, uint8_t clock_pin,
                uint8_t serial_output_pin)
  : _shift_load_pin{shift_load_pin},
    _clock_pin{clock_pin},
    _serial_output_pin{serial_output_pin} {}

uint8_t Shift74HC165::shift_in(void) const {
    const uint8_t retries = 3;
    uint8_t result = this->_hardware_shift_in();
    uint8_t current;

    for (uint8_t i = 0; i < retries - 1; ++i) {
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
  //TODO
  return 0;
}
