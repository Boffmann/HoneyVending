#include "Modules/ButtonRack.h"

#include <math.h>

#include "config.h"

const uint8_t log2(const uint8_t value) {
    // Round value up. This is expecially useful when two buttons were pressed
    // at a time
    return ceil(log(value) / log(2));
}

ButtonRack::ButtonRack() :
_button_shift_register(config::button_shift_load, config::button_clock, config::button_output)
{}

const bool ButtonRack::is_button_pressed(void) const {
    return false;
}

const uint8_t ButtonRack::get_pressed_button(void) const {
    const uint8_t pressed_button_binary = this->_button_shift_register.get_input();

    if (pressed_button_binary != NO_BUTTON) {
        return log2(pressed_button_binary);
    }

    return NO_BUTTON;
}
