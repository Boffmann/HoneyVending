#include "Shift74HC165.h"

#include <Arduino.h>

Shift74HC165::Shift74HC165(const uint8_t shift_load_pin, const uint8_t clock_pin,
                 const uint8_t serial_output_pin)
  : _shift_load_pin{shift_load_pin},
    _clock_pin{clock_pin},
    _serial_output_pin{serial_output_pin} {}


const uint8_t Shift74HC165::get_input(void) const {
  // Prepare to transmit data serially
  digitalWrite(_shift_load_pin, HIGH);
  digitalWrite(_clock_pin, HIGH);
  delay(50);
  // Shift in data
  const uint8_t shifted_in_data = _shift_in(MSBFIRST);
  // Allow parallel data to enter
  digitalWrite(_shift_load_pin, LOW);

  return shifted_in_data;
}

const uint8_t Shift74HC165::_shift_in(const uint8_t bit_order) const {
  uint8_t result = 0;
  uint8_t bit_index;
  
  for (bit_index = 0; bit_index < 7; ++bit_index) {
    digitalWrite(_clock_pin, HIGH);

    if (bit_order == LSBFIRST) {
      result |= digitalRead(_serial_output_pin) << bit_index;
    } else {
      result |= digitalRead(_serial_output_pin) << (7 - bit_index);
    }

    digitalWrite(_clock_pin, LOW);
  }

  // Last bit is handled outside the loop
  bit_index = 7;

  // For the last bit, the clock pin needs to stay high so that it is high for the next shift in
  // and the data that is shifted in is correct
  digitalWrite(_clock_pin, HIGH);
  if (bit_order == LSBFIRST) {
    result |= digitalRead(_serial_output_pin) << bit_index;
  } else {
    result |= digitalRead(_serial_output_pin) << (7 - bit_index);
  }

  return result;

}
