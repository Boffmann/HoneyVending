#ifndef _74HC165_H_
#define _74HC165_H_

#include <stdint.h>

const uint8_t NO_INPUT = 0;

class Shift74HC165 {

  public:

    /**
     * Constructor
     *
     * @param shift_load_pin The Shift register's shift load pin (latch pin)
     * @param clock_pin The Shift register's clock pin
     * @param serial_output_pin The Shift register's serial output pin
     */
    Shift74HC165(const uint8_t shift_load_pin, const uint8_t clock_pin,
                 const uint8_t serial_output_pin);

    /**
     * Function to shift in the Shift register's input
     *
     * @return The Shift registers value on its input pins
     */
    const uint8_t get_input(void) const;

  private:
    const uint8_t _shift_load_pin;
    const uint8_t _clock_pin;
    const uint8_t _serial_output_pin;

    /**
     * Personal implementation for shift in to be under control what happens
     */
    const uint8_t _shift_in(const uint8_t bit_order) const;

};

#endif
