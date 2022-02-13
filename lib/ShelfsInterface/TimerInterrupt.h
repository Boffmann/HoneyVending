#ifndef _TIMER_INTERRUPT_H_
#define _TIMER_INTERRUPT_H_

#include <stdint.h>

/**
 * Registers a new timer interrupt that ticks every X seconds
 * // TODO Define X
 */
void register_timer_interrupt();

uint32_t get_and_reset_timer_counter(void);

/**
 * @brief Triggers the timer. ATTENTION: Used for test purpose only
 */
void tick_timer_interrupt(void);

#endif