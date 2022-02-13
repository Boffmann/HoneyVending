#include "ButtonRack.h"

#include <Arduino.h>
#include <math.h>

static volatile bool interrupt_enabled_button_pressed;

static uint8_t log2(const uint8_t value) {
    // Round value up. This is expecially useful when two buttons were pressed
    // at a time
    return ceil(log(value) / log(2));
}

void IRAM_ATTR button_pressed_isr() {
    interrupt_enabled_button_pressed = true;
}

ButtonRack::ButtonRack(uint8_t shift_load_pin, uint8_t clock_pin, uint8_t output_pin, uint8_t pressed_interrupt) :
    _button_shift_register{
        shift_load_pin,
        clock_pin,
        output_pin}
{
    attachInterrupt(pressed_interrupt, button_pressed_isr, FALLING);
}

BUTTON ButtonRack::get_pressed_button(void) const {

    if (!interrupt_enabled_button_pressed) {
        return NO_BUTTON;
    }

    const uint8_t pressed_button_binary = this->_button_shift_register.shift_in();

    if (pressed_button_binary == NO_BUTTON) {
        return NO_BUTTON;
    }

    interrupt_enabled_button_pressed = false;
    return log2(pressed_button_binary);
}