#include "Data/Shelf.h"

Shelf::Shelf(const SHELF_ID id, const double price) 
    :   _id(id),
        _price(price),
        _is_open(false),
        _is_empty(false),
        _open_for(0) 
{}

SHELF_ID Shelf::get_id() const {
    return this->_id;
}

bool Shelf::open(double& debit) {

    if (this->_is_open || this->_is_empty || debit < this->_price) {
        return false;
    }

    this->_is_open = true;
    this->_open_for = 0;
    this->_is_empty = true;
    debit -= this->_price;

    return true;
}

void Shelf::close(void) {
    this->_is_open = false;
    this->_open_for = 0;
}

void Shelf::add_is_open_for(const uint8_t duration) {
    this->_open_for += duration;
}

uint8_t Shelf::get_is_open_time(void) const {
    return this->_open_for;
}
