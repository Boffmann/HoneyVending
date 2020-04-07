#include "Shelf.h"

#include <unity.h>
#include <Arduino.h>

#include "Shift74HC595.h"
#include "config.h"

Shelf shelf(
            new Shift74HC595(config::door_shift_register_clock,
                             config::door_storage_register_clock,
                             config::door_output,
                             config::door_output_enable)
);

void test_shelf_count(void) {

  TEST_ASSERT_EQUAL_INT8(shelf.get_shelf_count(), config::SHELF_COUNT);

}

void test_buy_shelf(void) {

  // Try buying shelf that does not exist
  TEST_ASSERT_EQUAL(shelf.buy_shelf(7, 600), false);
  TEST_ASSERT_EQUAL(shelf.buy_shelf(10, 800), false);

  // Try buying shelf with to less money
  TEST_ASSERT_EQUAL(shelf.buy_shelf(0, 300), false);
  TEST_ASSERT_EQUAL(shelf.buy_shelf(4, 499), false);

  // Try buying shelf with enough money
  TEST_ASSERT_EQUAL(shelf.buy_shelf(0, 500), true);
  TEST_ASSERT_EQUAL(shelf.buy_shelf(1, 1000), true);

  // Try to buy a shelf that was already bought
  TEST_ASSERT_EQUAL(shelf.buy_shelf(0, 600), false);

}

void setup() {

  pinMode(config::door_shift_register_clock, OUTPUT);
  pinMode(config::door_storage_register_clock, OUTPUT);
  pinMode(config::door_output, OUTPUT);
  pinMode(config::door_output_enable, OUTPUT);

  const uint8_t shelf_count = shelf.get_shelf_count();
  for (uint8_t shelf_index = 0; shelf_index < shelf_count; ++shelf_index) {
    shelf.set_shelf_price(shelf_index, 500);
  }

  UNITY_BEGIN();

  RUN_TEST(test_shelf_count);

  //RUN_TEST(test_buy_shelf);

  UNITY_END();
}


void loop() {

}
