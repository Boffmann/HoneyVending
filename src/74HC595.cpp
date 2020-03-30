#include "74HC595.h"

#include <Arduino.h>

74HC595::74HC595(const uint8_t overriding_clear_pin, const uint8_t output_enable_pin)
  : _overriding_clear_pin{overriding_clear_pin},
    _output_enable_pin{output_enable_pin} {
      clear_output();
      disable_output();
    }

void 74HC595::write_out(const uint8_t message) const {
  // The values are shifted into the storage register with a positive edge.
  // Prepare by setting it low
  digitalWrite(_storage_register_clock_pin, LOW);

  // Shift the data into the shift register
  shiftOut(_serial_input_pin, _shift_register_clock_pin, MSBFIRST, message);

  // Write the values into the storage register
  digitalWrite(_storage_register_clock_pin, HIGH);
}

void 74HC595::clear_shift_register() const {
  // Clear pin is active low
  digitalWrite(_overriding_clear_pin, LOW);

  delay(100);

  digitalWrite(_overriding_clear_pin, HIGH);
}

void 74HC595::enable_output() const {
  // Output enable pin is active low
  digitalWrite(_output_enable_pin, LOW);
}

void 74HC595::disable_output() const {
  digitalWrite(_output_enable_pin, HIGH);
}

void 74HC595::write_shift_to_storage_register() const {
  digitalWrite(_storage_register_clock_pin, LOW);
  delay(40);
  digitalWrite(_storage_register_clock_pin, HIGH);
}
