#include "74HC165.h"

#include <Arduino.h>


const uint8_t 74HC165::get_input() const {
  // Prepare to transmit data serially
  digitalWrite(_shift_load_pin, HIGH);
  // Shift in data
  const uint8_t shifted_in_data = shiftIn(_serial_output_pin, _clock_pin);
  // Allow parallel data to enter
  digitalWrite(_shift_load_pin, LOW);

  return shifted_in_data;
}
