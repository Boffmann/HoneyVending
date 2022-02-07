#include "Display.h"

#include <unity.h>
#include <Arduino.h>

#include "config.h"

Display display(config::segment_clock, config::segment_signal);

void test_get_number_of_digits(void) {
    TEST_ASSERT_EQUAL(display.get_number_of_digits(1), 1);
    TEST_ASSERT_EQUAL(display.get_number_of_digits(12), 2);
    TEST_ASSERT_EQUAL(display.get_number_of_digits(123), 3);
    TEST_ASSERT_EQUAL(display.get_number_of_digits(1234), 4);
    TEST_ASSERT_EQUAL(display.get_number_of_digits(12345), 5);
}

void test_get_digit(void) {
    uint16_t value = 1234;
    TEST_ASSERT_EQUAL(2, display.get_digit(value, 1));
    TEST_ASSERT_EQUAL(3, display.get_digit(value, 2));
    TEST_ASSERT_EQUAL(display.get_digit(12, 1), 2);
    TEST_ASSERT_EQUAL(display.get_digit(123, 1), 2);
    TEST_ASSERT_EQUAL(display.get_digit(1234, 0), 1);
    TEST_ASSERT_EQUAL(display.get_digit(1234, 1), 2);
    TEST_ASSERT_EQUAL(display.get_digit(1234, 2), 3);
    TEST_ASSERT_EQUAL(display.get_digit(1234, 3), 4);
    TEST_ASSERT_EQUAL(display.get_digit(56789, 4), 9);
}

void test_brightness(void) {

    display.set_brightness(BRIGHT_DARKEST);

    delay(5000);

    display.set_brightness(BRIGHT_TYPICAL);

    delay(5000);

    display.set_brightness(BRIGHTEST);

    delay(5000);

}

void test_show_digits(void) {

    /*display.show(1);
    delay(5000);
    display.show(12);
    delay(5000);
    display.show(123);
    delay(5000);
    display.show(1234);
    delay(5000);
    display.show(12345);
    delay(5000);*/

    display.show(223);

}

void setup() {

    pinMode(config::segment_clock, OUTPUT);
    pinMode(config::segment_signal, OUTPUT);

    display.init();
    display.set_brightness(BRIGHT_TYPICAL);

    UNITY_BEGIN();

    RUN_TEST(test_get_number_of_digits);
    RUN_TEST(test_get_digit);

    //RUN_TEST(test_brightness);
    RUN_TEST(test_show_digits);

    UNITY_END();

}

void loop() {

}