#ifndef _74HC595_h_
#define _74HC595_h_

#include <stdint.h>

class Shift74HC595 {
  public:
    Shift74HC595(const uint8_t shift_register_clock_pin, const uint8_t storage_register_clock_pin,
                 const uint8_t serial_input_pin, const uint8_t output_enable_pin);

    /**
     * Writes the bits in the message byte first into the shift register
     * and finally into the storage register
     *
     * @param message: The byte to write out
     */
    void write_out(const uint8_t message) const;

    /**
     * Clears the data in the shift register. Note that this does not propagate
     * the data into the storage register
     */
    void clear_shift_register(void) const;

    /**
     * Enable the output pins. This sets the output pins to the data in the
     * storage register
     */
    void enable_output(void) const;

    /**
     * Disables the output pins.
     */
    void disable_output(void) const;

    /**
     * Manually write the data in the shift register into the storage register
     */
    void write_shift_to_storage_register(void) const;


  private:
    const uint8_t _shift_register_clock_pin;
    const uint8_t _storage_register_clock_pin;
    const uint8_t _serial_input_pin;
    const uint8_t _output_enable_pin;
};

#endif
