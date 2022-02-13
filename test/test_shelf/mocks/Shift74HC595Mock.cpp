#include "Shift74HC595.h"


Shift74HC595::Shift74HC595(uint8_t shift_register_clock_pin, uint8_t storage_register_clock_pin,
                 uint8_t serial_input_pin, uint8_t output_enable_pin)
  : _shift_register_clock_pin{shift_register_clock_pin},
    _storage_register_clock_pin{storage_register_clock_pin},
    _serial_input_pin{serial_input_pin},
    _output_enable_pin{output_enable_pin} {}

void Shift74HC595::shift_out(uint8_t message) const {

}

void Shift74HC595::_enable_output(void) const {
  
}

void Shift74HC595::_disable_output(void) const {
  
}