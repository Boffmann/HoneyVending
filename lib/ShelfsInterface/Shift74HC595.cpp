#include "Shift74HC595.h"

#include <Arduino.h>

Shift74HC595::Shift74HC595(const uint8_t shift_register_clock_pin, const uint8_t storage_register_clock_pin,
                 const uint8_t serial_input_pin, const uint8_t output_enable_pin)
  : _shift_register_clock_pin{shift_register_clock_pin},
    _storage_register_clock_pin{storage_register_clock_pin},
    _serial_input_pin{serial_input_pin},
    _output_enable_pin{output_enable_pin} {


  pinMode(_shift_register_clock_pin, OUTPUT);
  pinMode(_storage_register_clock_pin, OUTPUT);
  pinMode(_serial_input_pin, OUTPUT);
  pinMode(_output_enable_pin, OUTPUT);
  shift_out(0);
}

// ATTENTION At least 100ns required between flanks. CPU should
// run <10MHZ (100ns period) or add delays
void Shift74HC595::shift_out(uint8_t message) const {

  // Disable storage register outputs to be unaffected
  // by shift. This allows to enable the finished 
  digitalWrite(_output_enable_pin, HIGH);

  // Set ShiftRegister clock low because it's triggered on rising
  // edge
  digitalWrite(_shift_register_clock_pin, LOW);

  // The values are shifted into the storage register with a positive edge.
  // Prepare by setting it low
  digitalWrite(_storage_register_clock_pin, LOW);

  // Shift the data into the shift register
  shiftOut(_serial_input_pin, _shift_register_clock_pin, MSBFIRST, message);

  // Write the values into the storage register
  digitalWrite(_storage_register_clock_pin, HIGH);

  // Enable output again
  digitalWrite(_output_enable_pin, LOW);
}
