#ifndef _74HC595_h_
#define _74HC595_h_

#include <stdint.h>

class Shift74HC595 {
  public:
    Shift74HC595(uint8_t shift_register_clock_pin, uint8_t storage_register_clock_pin,
                 uint8_t serial_input_pin, uint8_t output_enable_pin);

    /**
     * Writes the bits in the message byte out to the shift register
     *
     * @param message: The byte to write out
     */
    void shift_out(uint8_t message) const;


  private:
    const uint8_t _shift_register_clock_pin;
    const uint8_t _storage_register_clock_pin;
    const uint8_t _serial_input_pin;
    const uint8_t _output_enable_pin;
};

#endif