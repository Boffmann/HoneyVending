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

  if (!_is_shelf_full[shelf_number]) {
    return false;
  }

  _open_door(shelf_number);

  delay(9900);

  _close_doors();

  _is_shelf_full[shelf_number] = false;

  return true;
}

const uint8_t Shelf::get_shelf_count(void) {

  return config::SHELF_COUNT;

}

void Shelf::_open_door(const uint8_t door_number) const {

  // Create power of two value to open correct door
  const uint8_t door_to_open = pow(2, door_number);

  _door_shift_register->disable_output();

  _door_shift_register->write_out(door_to_open);

  delay(50);

  _door_shift_register->enable_output();

}

void Shelf::_close_doors(void) const {

  _door_shift_register->disable_output();

  _door_shift_register->clear_shift_register();

  delay(50);

  _door_shift_register->enable_output();

}