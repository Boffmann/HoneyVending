#include "SIPO.h"

SIPO::SIPO(const uint8_t shift_register_clock_pin,
    const uint8_t storage_register_clock_pin, const uint8_t serial_input_pin)
  : _shift_register_clock_pin{shift_register_clock_pin},
    _storage_register_clock_pin{storage_register_clock_pin},
    _serial_input_pin{serial_input_pin} {}
