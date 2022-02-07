#include "Hardware/Shift74HC595.h"

#include <Arduino.h>

Shift74HC595::Shift74HC595(const uint8_t shift_register_clock_pin, const uint8_t storage_register_clock_pin,
                 const uint8_t serial_input_pin, const uint8_t output_enable_pin)
  : _shift_register_clock_pin{shift_register_clock_pin},
    _storage_register_clock_pin{storage_register_clock_pin},
    _serial_input_pin{serial_input_pin},
    _output_enable_pin{output_enable_pin} {

      write_out(0);
      _disable_output();
    }

void Shift74HC595::write_out(const uint8_t message) const {

  // The values are shifted into the storage register with a positive edge.
  // Prepare by setting it low
  digitalWrite(_storage_register_clock_pin, LOW);

  // Shift the data into the shift register
  shiftOut(_serial_input_pin, _shift_register_clock_pin, MSBFIRST, message);

  // Write the values into the storage register
  digitalWrite(_storage_register_clock_pin, HIGH);
}

void Shift74HC595::_enable_output(void) const {
  // Output enable pin is active low
  digitalWrite(_output_enable_pin, LOW);
}

void Shift74HC595::_disable_output(void) const {
  digitalWrite(_output_enable_pin, HIGH);
}
