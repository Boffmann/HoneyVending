#include <Arduino.h>
#include<avr/sleep.h>

#include "config.h"
#include "CoinSerial.h"

volatile boolean running = false;
CoinSerial coin_serial(config::coin_rx, config::coin_tx);

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
    // Enable sleep mode
    sleep_enable();
    // Attach coin input interrupt to wakeup. Wakeup on pin change
    attachInterrupt(config::coin_rx_interrupt, coin_inserted_isr, CHANGE);
    // Go to full sleep
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    // Give some time before going to sleep
    delay(100);
    sleep_cpu()
}

void loop() {
    // Give the device some time to start
    delay(3000);
    // Go to sleep and wait for coin to be inserted
    goodnight_arduino();
    
    while (running) {

    }

}

void reset_isr() {
    // TODO
}

void wakeUp() {

    running = true;
}