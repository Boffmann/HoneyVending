#include "Shift74HC165.h"

#include <Arduino.h>

Shift74HC165::Shift74HC165(const uint8_t shift_load_pin, const uint8_t clock_pin,
                 const uint8_t serial_output_pin)
  : PISO::PISO(shift_load_pin, clock_pin, serial_output_pin) {}


const uint8_t Shift74HC165::get_input() const {
  // Prepare to transmit data serially
  digitalWrite(_shift_load_pin, HIGH);
  // Shift in data
  const uint8_t shifted_in_data = shiftIn(_serial_output_pin, _clock_pin, MSBFIRST);
  // Allow parallel data to enter
  digitalWrite(_shift_load_pin, LOW);

  return shifted_in_data;
}
