#ifndef _74HC165_H_
#define _74HC165_H_

#include "PISO.h"

#include <cstdint>


class 74HC165 : public PISO {

  public:

    /**
     * Read the input byte on the parallel input pins and return it
     *
     * @return The byte on the parallel input pins
     */
    const uint8_t get_input() const;

};

#endif
