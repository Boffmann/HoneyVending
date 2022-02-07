#include "Modules/ShelfsInterface.h"

#include <Arduino.h>

// In Seconds
const uint8_t INTERRUPT_DURATION = 5;

void ShelfsInterface::add_shelf(const SHELF id, const uint32_t price) {
  this->_shelfs[id] = Shelf(id, price);
}

const bool ShelfsInterface::buy_shelf(const SHELF shelf_id, uint32_t &debit) {
  Shelf& shelf_to_open = this->_shelfs[shelf_id];

  if (shelf_to_open.is_open()) {
    return false;
  }
  if (shelf_to_open.get_price() > debit) {
    return false;
  }

  // Create power of two value to open correct door
  const uint8_t door_to_open = pow(2, shelf_id);
  this->_door_shift_register.write_out(door_to_open);
  shelf_to_open.set_open();
  this->_open_shelfs.insert(shelf_to_open);
  debit -= shelf_to_open.get_price();
  return true;
}

void ShelfsInterface::close_overdue_shelfs(void) {
  // Safe copy of passed timers and substract to not miss changes in interrupt
  uint8_t local_passed_timers = this->_passed_timers;
  this->_passed_timers -= local_passed_timers;

  const node_t *current = this->_open_shelfs.get_first();
  while (current != nullptr) {
    Shelf& processed_shelf = this->_open_shelfs.get_shelf(*current);
    processed_shelf.add_is_open_for(local_passed_timers * INTERRUPT_DURATION);
    if (this->_should_close(processed_shelf)) {
      this->_close_shelf(processed_shelf);
      this->_open_shelfs.remove(processed_shelf);
    }
    current = this->_open_shelfs.get_next(*current);
  }  
}

void ShelfsInterface::_close_shelf(Shelf& shelf) {
  // TODO implement than only one door can be closed when multiple open
  this->_door_shift_register.write_out(0);
  shelf.set_closed();
}
