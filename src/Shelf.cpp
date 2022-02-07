#include "Data/Shelf.h"

Shelf::Shelf(const SHELF id, const uint32_t price) 
    :   _id(id), 
        _price(price),
        _is_open(false),
        _is_empty(false),
        _open_for(0) 
{}

const uint32_t Shelf::get_price(void) const {
    return this->_price;
}

const bool Shelf::is_open(void) const {
    return this->_is_open;
}

void Shelf::set_open(void) {
    this->_is_open = true;
    this->_open_for = 0;
    this->_is_empty = true;
}

void Shelf::set_closed(void) {
    this->_is_open = false;
}

void Shelf::add_is_open_for(const uint8_t duration) {
    this->_open_for += duration;
}

const uint8_t Shelf::get_is_open_time(void) const {
    return this->_open_for;
}