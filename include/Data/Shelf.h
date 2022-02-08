#ifndef _HV_SHELF_H_
#define _HV_SHELF_H_

#include <stdint.h>
#include <stdio.h>

typedef uint8_t SHELF_ID;
const SHELF_ID NO_SHELF = 0;
const SHELF_ID SHELF_1 = 1;
const SHELF_ID SHELF_2 = 2;
const SHELF_ID SHELF_3 = 3;
const SHELF_ID SHELF_4 = 4;
const SHELF_ID SHELF_5 = 5;
const SHELF_ID SHELF_6 = 6;
const SHELF_ID MAX_SHELF_ID = SHELF_6;

class Shelf {

public:

    Shelf(const SHELF_ID id, const double price);

    SHELF_ID get_id() const;

    bool open(double&);

    void close(void);

    void add_is_open_for(const uint8_t duration);

    uint8_t get_is_open_time(void) const;

    inline bool operator==(const Shelf& other) const {
        return this->_id == other._id;
     }

private:
    SHELF_ID _id;
    double _price;
    bool _is_open;
    bool _is_empty;
    /** Duration for how long this shelf is open in seconds */
    uint8_t _open_for;

};

#endif
