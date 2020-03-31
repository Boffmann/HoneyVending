#ifndef _SIPO_SHIFT_H_
#define _SIPO_SHIFT_H_

#include <stdint.h>

class SIPO {

  public:
    SIPO(const uint8_t shift_register_clock_pin, const uint8_t storage_register_clock_pin,
         const uint8_t serial_input_pin);

    virtual void write_out(const uint8_t message) const = 0;

  protected:
    const uint8_t _shift_register_clock_pin;
    const uint8_t _storage_register_clock_pin;
    const uint8_t _serial_input_pin;

};

#endif
