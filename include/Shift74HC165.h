#ifndef _74HC165_H_
#define _74HC165_H_

#include "PISO.h"

#include <stdint.h>


class Shift74HC165 : public PISO {

  public:

    Shift74HC165(const uint8_t shift_load_pin, const uint8_t clock_pin,
                 const uint8_t serial_output_pin);

    /**
     * Read the input byte on the parallel input pins and return it
     *
     * @return The byte on the parallel input pins
     */
    const uint8_t get_input() const override;

};

#endif
