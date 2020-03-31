#ifndef _PISO_SHIFT_H_
#define _PISO_SHIFT_H_

#include <stdint.h>

class PISO {

  public:
    PISO(const uint8_t shift_load_pin, const uint8_t clock_pin,
         const uint8_t serial_output_pin);
    virtual const uint8_t get_input() const = 0;

  protected:
    const uint8_t _shift_load_pin;
    const uint8_t _clock_pin;
    const uint8_t _serial_output_pin;

};

#endif
