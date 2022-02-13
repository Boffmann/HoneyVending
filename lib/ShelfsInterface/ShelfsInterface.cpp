#include "ShelfsInterface.h"

#include <math.h>
#include <stdio.h>

#include "TimerInterrupt.h"

// In Seconds
const static uint8_t INTERRUPT_DURATION = 10;

ShelfsInterface::ShelfsInterface( uint8_t clock_pin,
                                  uint8_t storage_clock_pin,
                                  uint8_t output_pin,
                                  uint8_t output_enable_pin)
    : _door_shift_register{
          clock_pin,
          storage_clock_pin,
          output_pin,
          output_enable_pin},
      _shelfs{
          Shelf(SHELF_1, 5.0),
          Shelf(SHELF_2, 5.0),
          Shelf(SHELF_3, 5.0),
          Shelf(SHELF_4, 5.0),
          Shelf(SHELF_5, 5.0),
          Shelf(SHELF_6, 5.0)}
{
  register_timer_interrupt();
}

bool ShelfsInterface::buy_shelf(const SHELF_ID shelf_id, double &debit) {

  Shelf *shelf_to_open = nullptr;
  
  if (!_get_shelf_by_id(shelf_id, &shelf_to_open)) {
    return false;
  }

  if (!shelf_to_open->open(debit)) {
      return false;
  }

  this->_open_shelfs.insert(*shelf_to_open);

  this->_door_shift_register.shift_out(open_shelfs_to_bit_mask());

  return true;
}

uint8_t ShelfsInterface::close_overdue_shelfs(void) {
  uint8_t number_closed = 0;
  uint32_t passed_timers = get_and_reset_timer_counter();

  const node_t *current = this->_open_shelfs.get_first();
  while (current != nullptr) {
    Shelf& processed_shelf = this->_open_shelfs.get_shelf(current);
    processed_shelf.add_is_open_for(passed_timers * INTERRUPT_DURATION);
    if (this->_should_close(processed_shelf)) {
      this->_close_shelf(processed_shelf);
      number_closed++;
    }
    current = this->_open_shelfs.get_next(current);
  }

  return number_closed;
}

OpenShelfList& ShelfsInterface::get_open_shelfs(void) {
  return this->_open_shelfs;
}

uint8_t ShelfsInterface::open_shelfs_to_bit_mask(void) const {
  uint8_t result = 0x0;

  const node_t *current = this->_open_shelfs.get_first();
  while (current != nullptr) {
    SHELF_ID id = this->_open_shelfs.get_shelf(current).get_id();
    result |= (uint8_t)ceil(pow(2, id - 1));
    current = this->_open_shelfs.get_next(current);
  }

  return result;
}
