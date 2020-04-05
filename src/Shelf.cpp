#include "Shelf.h"

#include <Arduino.h>

Shelf::Shelf(const Shift74HC595* const door_shift_register)
  :  _door_shift_register{door_shift_register} {

    for (uint8_t shelf_index = 0; shelf_index < config::SHELF_COUNT; ++shelf_index) {
      _shelf_prices[shelf_index] = 0;
      _is_shelf_full[shelf_index] = true;
    }

}

Shelf::~Shelf(void) {

  delete _door_shift_register;

}

void Shelf::set_shelf_price(const uint8_t shelf_number, const uint16_t shelf_price) {

  if (shelf_number < config::SHELF_COUNT) {
    _shelf_prices[shelf_number] = shelf_price;
  }

}

bool Shelf::buy_shelf(const uint8_t shelf_number, const uint16_t money) {

  if (!(shelf_number < config::SHELF_COUNT)) {
    return false;
  }

  if (money < _shelf_prices[shelf_number]) {
    return false;
  }

  // Create power of two value to open correct door
  uint8_t door_to_open = pow(2, shelf_number);

  _door_shift_register->disable_output();

  _door_shift_register->write_out(door_to_open);

  delay(50);

  _door_shift_register->enable_output();

  delay(9900);

  _door_shift_register->disable_output();

  _door_shift_register->write_out(door_to_open);

  delay(50);

  _door_shift_register->enable_output();

  _is_shelf_full[shelf_number] = false;

  return true;
}
