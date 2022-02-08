#include "Hardware/TimerInterrupt.h"

uint32_t interrupt_counter;

bool running = false;

void register_timer_interrupt() {

    // Only one timer interrupt is allowed
    if (running) {
        return;
    }

    interrupt_counter = 0;
}

uint32_t get_and_reset_timer_counter(void) {
    uint32_t counter = interrupt_counter;
    interrupt_counter = 0;

    return counter;
}

void tick_timer_interrupt(void) {
    interrupt_counter++;
}
