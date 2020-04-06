#include "ButtonRack.h"

#include <math.h>

ButtonRack::ButtonRack(const Shift74HC165* const button_shift_register)
  : _button_shift_register{button_shift_register} {}

ButtonRack::~ButtonRack(void) {

 delete _button_shift_register;

}

const uint8_t ButtonRack::get_pressed_button(void) const {
    const uint8_t pressed_button_binary = _button_shift_register->get_input();

    if (pressed_button_binary != NO_INPUT) {
        return log2(pressed_button_binary);
    }

    return NO_INPUT;
}

const uint8_t ButtonRack::log2(const uint8_t value) const {
    // Round value up. This is expecially useful when two buttons were pressed
    // at a time
    return ceil(log(value) / log(2));
}