#include <Arduino.h>
#include<avr/sleep.h>

#include "config.h"
#include "CoinSerial.h"

boolean running = false;
volatile boolean reset = false;
uint8_t pressed_button = 0;
CoinSerial coin_serial(config::coin_rx, config::coin_tx);
74HC165 button_shift_register(config::button_shift_load,
                              config::button_clock,
                              config::button_output);

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

    coin_serial.begin();

    // Attach reset Pin's interrupt routine
    attachInterrupt(digitalPinToInterrupt(config::reset_button), reset_isr, RISING);
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
    // Give the device some time to start
    delay(3000);
    // Go to sleep and wait for coin to be inserted
    goodnight_arduino();

    // Run after waking up
    if (reset) {
        // TODO
    } else {
        running = true;
    }
    
    while (running) {
        coin_serial.update();
        pressed_button = button_shift_register.get_input();
    }

}

void reset_isr() {
    reset = true;
}