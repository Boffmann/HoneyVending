#include "Shelf.h"

Shelfs::Shelfs(const uint8_t shelf_count, std::unique_ptr<74HC595> door_shift_register)
  : _shelf_count{shelf_count},
    _door_shift_register(std::move(door_shift_register)) {

    _shelf_prices = std::vector<uint16_t>(_shelf_count, 0);
    _is_shelf_full = std::vector<boolean>(_shelf_count, true);

  }

void Shelfs::set_shelf_price(const uint8_t shelf_number, const uint8_t shelf_price) {

  if (shelf_number < _shelf_count) {
    _shelf_prices[shelf_number] = shelf_price;
  }

}

boolean Shelfs::buy_shelf(const uint8_t shelf_number, const uint16_t money) {

  if (!shelf_number < _shelf_count) {
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
