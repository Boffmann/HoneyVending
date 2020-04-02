#include "Shift74HC595.h"

#include <unity.h>
#include <Arduino.h>

#include "config.h"

const Shift74HC595 shift = Shift74HC595(config::door_shift_register_clock,
                                        config::door_storage_register_clock,
                                        config::door_output,
                                        config::door_output_enable);

void test_write_out(void) {

  digitalWrite(config::door_storage_register_clock, LOW);
  delay(50);
  TEST_ASSERT_EQUAL(LOW, digitalRead(config::door_storage_register_clock));

  shift.write_out(1);

  delay(50);

  TEST_ASSERT_EQUAL(HIGH, digitalRead(config::door_storage_register_clock));

}

void test_clear_shift_register(void) {
  digitalWrite(config::door_storage_register_clock, LOW);
  delay(50);
  TEST_ASSERT_EQUAL(LOW, digitalRead(config::door_storage_register_clock));

  shift.clear_shift_register();

  delay(50);

  TEST_ASSERT_EQUAL(HIGH, digitalRead(config::door_storage_register_clock));
}

void test_enable_output(void) {
  digitalWrite(config::door_output_enable, HIGH);
  delay(50);
  TEST_ASSERT_EQUAL(HIGH, digitalRead(config::door_output_enable));

  shift.enable_output();

  delay(50);

  TEST_ASSERT_EQUAL(LOW, digitalRead(config::door_output_enable));
}

void test_disable_output(void) {
  digitalWrite(config::door_output_enable, LOW);
  delay(50);
  TEST_ASSERT_EQUAL(LOW, digitalRead(config::door_output_enable));

  shift.disable_output();

  delay(50);

  TEST_ASSERT_EQUAL(HIGH, digitalRead(config::door_output_enable));
}

void test_write_shift_to_storage_register(void) {
  digitalWrite(config::door_storage_register_clock, LOW);
  delay(50);
  TEST_ASSERT_EQUAL(LOW, digitalRead(config::door_storage_register_clock));

  shift.write_shift_to_storage_register();

  delay(50);

  TEST_ASSERT_EQUAL(HIGH, digitalRead(config::door_storage_register_clock));
}


void test_playground(void) {
  shift.disable_output();
  delay(50);
  shift.write_out(1);
  delay(50);
  shift.enable_output();

  delay(5000);

  shift.disable_output();
  delay(50);
  shift.write_out(2);
  delay(50);
  shift.enable_output();

  delay(5000);

  shift.disable_output();
}



void setup() {
  pinMode(config::door_shift_register_clock, OUTPUT);
  pinMode(config::door_storage_register_clock, OUTPUT);
  pinMode(config::door_output, OUTPUT);
  pinMode(config::door_output_enable, OUTPUT);

  UNITY_BEGIN();

  /*RUN_TEST(test_write_out);
  RUN_TEST(test_clear_shift_register);
  RUN_TEST(test_enable_output);
  RUN_TEST(test_disable_output);
  RUN_TEST(test_write_shift_to_storage_register);*/

  RUN_TEST(test_playground);

  UNITY_END();
}

void loop() {

}