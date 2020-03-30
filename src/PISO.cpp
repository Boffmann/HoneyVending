#include "PISO.h"

PISO::PISO(const uint8_t shift_load_pin, const uint8_t clock_pin,
                 const uint8_t serial_output_pin)
  : _shift_load_pin{shift_load_pin},
    _shift_clock_pin{clock_pin},
    _serial_output_pin{serial_output_pin} {}
