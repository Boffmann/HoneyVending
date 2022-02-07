#ifndef _HONEY_VENDING_BUTTON_RACK_H_
#define _HONEY_VENDING_BUTTON_RACK_H_

#include <stdint.h>

#include "Hardware/Shift74HC165.h"

typedef uint8_t BUTTON;

const BUTTON NO_BUTTON = 0;
const BUTTON BUTTON_1 = 1;
const BUTTON BUTTON_2 = 2;
const BUTTON BUTTON_3 = 3;
const BUTTON BUTTON_4 = 4;
const BUTTON BUTTON_5 = 5;
const BUTTON BUTTON_6 = 6;

/**
 * A class that wraps the button shift register to make it suitable for HoneyVending
 */
class ButtonRack {

  public:

    ButtonRack();

    /**
     * Returns true if a button is pressed, false otherwise
     */
    const bool is_button_pressed(void) const;

    /**
     * Return the button that has been pressed
     */
    const BUTTON get_pressed_button(void) const;


  private:
    const Shift74HC165 _button_shift_register;

    // Do not allow copying
    ButtonRack(const ButtonRack& other);
    ButtonRack& operator=(const ButtonRack& other);

};

#endif