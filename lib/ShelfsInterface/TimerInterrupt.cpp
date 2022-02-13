#include "Hardware/TimerInterrupt.h"

#include <Arduino.h>

hw_timer_t *timer;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
volatile uint32_t interrupt_counter;

bool running = false;

void IRAM_ATTR onTimer() {
    portENTER_CRITICAL_ISR(&timerMux);
    interrupt_counter++;
    portEXIT_CRITICAL_ISR(&timerMux);
}

void register_new_timer_interrupt() {

    // Only one timer interrupt is allowed
    if (running) {
        return;
    }

    interrupt_counter = 0;

    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 1000000, true);
    timerAlarmEnable(timer);
    running = true;
}

uint32_t get_and_reset_timer_counter(void) {
    uint32_t counter; 
    portENTER_CRITICAL_ISR(&timerMux);
    counter = interrupt_counter;
    interrupt_counter = 0;
    portEXIT_CRITICAL_ISR(&timerMux);

    return counter;
}