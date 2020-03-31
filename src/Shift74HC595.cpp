#include "Shift74HC595.h"

#include <Arduino.h>

Shift74HC595::Shift74HC595(const uint8_t shift_register_clock_pin, const uint8_t storage_register_clock_pin,
                 const uint8_t serial_input_pin, const uint8_t output_enable_pin)
  : SIPO::SIPO{shift_register_clock_pin, storage_register_clock_pin, serial_input_pin},
    _output_enable_pin{output_enable_pin} {

      clear_shift_register();
      disable_output();
    } 

void Shift74HC595::write_out(const uint8_t message) const {
  // The values are shifted into the storage register with a positive edge.
  // Prepare by setting it low
  digitalWrite(_storage_register_clock_pin, LOW);

  // Shift the data into the shift register
  shiftOut(_serial_input_pin, SIPO::_shift_register_clock_pin, MSBFIRST, message);

  // Write the values into the storage register
  digitalWrite(_storage_register_clock_pin, HIGH);
}

void Shift74HC595::clear_shift_register() const {
  // Clear the register by writing 0 to it

  write_out(0);
}

void Shift74HC595::enable_output() const {
  // Output enable pin is active low
  digitalWrite(_output_enable_pin, LOW);
}

void Shift74HC595::disable_output() const {
  digitalWrite(_output_enable_pin, HIGH);
}

void Shift74HC595::write_shift_to_storage_register() const {
  digitalWrite(_storage_register_clock_pin, LOW);
  delay(40);
  digitalWrite(_storage_register_clock_pin, HIGH);
}
