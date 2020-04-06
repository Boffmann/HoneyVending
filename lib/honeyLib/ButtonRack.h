#ifndef _HONEY_VENDING_BUTTON_RACK_H_
#define _HONEY_VENDING_BUTTON_RACK_H_

#include <stdint.h>

#include "Shift74HC165.h"

/**
 * A class that wraps the button shift register to make it suitable for HoneyVending
 */
class ButtonRack {

  public:

    ButtonRack(const Shift74HC165* const button_shift_register);
    ~ButtonRack();

    const uint8_t get_pressed_button(void) const;

    /**
     * Calculate log2.
     * log(2,x) = log(m,x) / log(m, 2)
     * 
     * @param value Value to calculate log from
     * @return the logarithm
     */
    const uint8_t log2(const uint8_t value) const;


  private:
    const Shift74HC165* const _button_shift_register;

    // Do not allow copying
    ButtonRack(const ButtonRack& other);
    ButtonRack& operator=(const ButtonRack& other);

};

#endif