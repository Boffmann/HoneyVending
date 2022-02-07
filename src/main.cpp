#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>

#include "config.h"
#include "Hardware/CoinSerial.h"
#include "Hardware/Shift74HC165.h"
#include "Hardware/Shift74HC595.h"
#include "Hardware/Display.h"

boolean running = false;
volatile boolean reset = false;
uint8_t pressed_button = 0;
Shift74HC165 button_shift_register(config::button_shift_load,
                              config::button_clock,
                              config::button_output);

Display display(config::segment_clock, config::segment_signal);

void reset_isr() {
    reset = true;
}

void setup() {
    // Set pin modes
    pinMode(config::reset_button, INPUT);
    pinMode(config::coin_rx, INPUT);
    pinMode(config::button_shift_load, OUTPUT);
    pinMode(config::button_clock, OUTPUT);
    pinMode(config::button_output, INPUT);
    pinMode(config::segment_signal, OUTPUT);
    pinMode(config::segment_clock, OUTPUT);
    pinMode(config::door_output, OUTPUT);
    pinMode(config::door_storage_register_clock, OUTPUT);
    pinMode(config::door_shift_register_clock, OUTPUT);
    pinMode(config::door_output_enable, OUTPUT);
    pinMode(config::coin_tx, OUTPUT);

    CoinSerial::begin(4800);
    display.init();
    display.set_brightness(BRIGHT_TYPICAL);

    // Attach reset Pin's interrupt routine
    //attachInterrupt(digitalPinToInterrupt(config::reset_button), reset_isr, RISING);
}

/**
 * Puts the Arduino to sleep. Defines interrupt for coin
 * serial to make it wake up
 */
void goodnight_arduino() {
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();

    // Disable everything but usart to get inserted coins
    power_adc_disable();
    power_spi_disable();
    power_timer0_disable();
    power_timer1_disable();
    power_timer2_disable();
    power_twi_disable();

    // Now put device actually to sleep
    sleep_mode();

    // PROGRAM CONTINUES FROM HERE AFTER WAKING UP
    sleep_disable();

    power_all_enable();
}

void loop() {
    goodnight_arduino();
}
