#ifndef _SHELF_H_
#define _SHELF_H_

#include <stdint.h>

typedef uint8_t SHELF;
const SHELF NO_SHELF = 0;
const SHELF SHELF_1 = 1;
const SHELF SHELF_2 = 2;
const SHELF SHELF_3 = 3;
const SHELF SHELF_4 = 4;
const SHELF SHELF_5 = 5;
const SHELF SHELF_6 = 6;


class Shelf {

public:

    Shelf(const SHELF id, const uint32_t price);

    const uint32_t get_price(void) const;

    const bool is_open(void) const;

    void set_open(void);

    void set_closed(void);

    void add_is_open_for(const uint8_t duration);

    const uint8_t get_is_open_time(void) const;

private:
    SHELF _id;
    uint32_t _price;
    bool _is_open;
    bool _is_empty;
    /** Duration for how long this shelf is open in seconds */
    uint8_t _open_for;

};

#endif