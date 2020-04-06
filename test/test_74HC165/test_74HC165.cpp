#include "Shift74HC165.h"

#include <unity.h>
#include <Arduino.h>

#include "config.h"

Shift74HC165 shift(config::button_shift_load, config::button_clock, config::button_output);

bool running = true;

uint8_t button_input = NO_INPUT;

void test_input(void) {

button_input = shift.get_input();

while (true) {
    delay(50);
    button_input = shift.get_input();

    if (button_input != NO_INPUT) {
        TEST_ASSERT_EQUAL(32, button_input);
        break;
    }

    TEST_ASSERT_EQUAL(button_input, NO_INPUT);

}

}

void setup() {

    pinMode(config::button_shift_load, OUTPUT);
    pinMode(config::button_clock, OUTPUT);
    pinMode(config::button_output, INPUT);

}

void loop() {

    UNITY_BEGIN();

    RUN_TEST(test_input);

    UNITY_END();
}