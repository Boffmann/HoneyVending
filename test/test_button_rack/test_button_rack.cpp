#include "ButtonRack.h"

#include <unity.h>
#include <Arduino.h>

#include "Shift74HC165.h"
#include "config.h"

ButtonRack rack(new Shift74HC165(config::button_shift_load, config::button_clock, config::button_output));

void test_convert_button(void) {
    TEST_ASSERT_EQUAL(0, convert_pressed_button(1));
    TEST_ASSERT_EQUAL(1, convert_pressed_button(2));
    TEST_ASSERT_EQUAL(2, convert_pressed_button(4));
    TEST_ASSERT_EQUAL(3, convert_pressed_button(8));
    TEST_ASSERT_EQUAL(4, convert_pressed_button(16));
    TEST_ASSERT_EQUAL(5, convert_pressed_button(32));
    TEST_ASSERT_EQUAL(6, convert_pressed_button(64));
    TEST_ASSERT_EQUAL(7, convert_pressed_button(128));


    TEST_ASSERT_EQUAL(6, convert_pressed_button(33));
    TEST_ASSERT_EQUAL(8, convert_pressed_button(255));
    TEST_ASSERT_EQUAL(4, convert_pressed_button(9));
    TEST_ASSERT_EQUAL(3, convert_pressed_button(7));
    TEST_ASSERT_EQUAL(5, convert_pressed_button(21));
}

void setup() {
    UNITY_BEGIN();

    RUN_TEST(test_convert_button);

    UNITY_END();

}

void loop() {

}