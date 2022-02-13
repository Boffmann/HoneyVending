#ifndef _74HC165_H_
#define _74HC165_H_

#include <stdint.h>

class Shift74HC165 {

  public:

    /**
     * Constructor
     *
     * @param shift_load_pin The Shift register's shift load pin (latch pin)
     * @param clock_pin The Shift register's clock pin
     * @param serial_output_pin The Shift register's serial output pin
     */
    Shift74HC165(uint8_t shift_load_pin, uint8_t clock_pin,
                 uint8_t serial_output_pin);

    /**
     * Read from the shift register and return the read byte.
     * This implements a debouncing strategy. Result must be the same
     * for 300ms in order to be accepted as input
     *
     * @return The Shift registers value on its input pins
     */
    uint8_t shift_in(void) const;

  private:
    const uint8_t _shift_load_pin;
    const uint8_t _clock_pin;
    const uint8_t _serial_data_pin;

    uint8_t _hardware_shift_in(void) const;

};

#endif