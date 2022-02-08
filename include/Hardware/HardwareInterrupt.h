#ifndef _HARDWARE_INTERRUPT_H_
#define _HARDWARE_INTERRUPT_H_

#include <stdint.h>

enum HW_INTERRUPT_MODE{
    FALLING = 0,
    RISING = 1
};

void register_hardware_interrupt(uint8_t, HW_INTERRUPT_MODE);

bool hw_interrupt_is_active(void);

void hw_interrupt_clear(void);

#endif