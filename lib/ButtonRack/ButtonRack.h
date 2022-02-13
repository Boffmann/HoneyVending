#ifndef _HV_BUTTON_RACK_H_
#define _HV_BUTTON_RACK_H_

#include <stdint.h>

#include "Shift74HC165.h"

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

    ButtonRack(uint8_t, uint8_t, uint8_t, uint8_t);

    /**
     * Return the currently pressed button.
     * If no button is pressed, NO_BUTTON is returned
     */
    BUTTON get_pressed_button(void) const;


  private:
    const Shift74HC165 _button_shift_register;

    // Do not allow copying
    ButtonRack(const ButtonRack& other);
    ButtonRack& operator=(const ButtonRack& other);

};

#endif