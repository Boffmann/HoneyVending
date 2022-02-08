#include "Modules/ButtonRack.h"

#include <math.h>

#include "config.h"

uint8_t log2(const uint8_t value) {
    // Round value up. This is expecially useful when two buttons were pressed
    // at a time
    return ceil(log(value) / log(2));
}

ButtonRack::ButtonRack() :
    _button_shift_register{
        config::button_shift_load,
        config::button_clock,
        config::button_output}
{
    register_hardware_interrupt(config::button_rack_interrupt, FALLING);
}

BUTTON ButtonRack::get_pressed_button(void) const {

    if (!hw_interrupt_is_active()) {
        return NO_BUTTON;
    }

    const uint8_t pressed_button_binary = this->_button_shift_register.shift_in();

    if (pressed_button_binary == NO_BUTTON) {
        return NO_BUTTON;
    }

    hw_interrupt_clear();
    return log2(pressed_button_binary);
}