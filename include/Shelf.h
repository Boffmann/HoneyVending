#ifndef _HONEY_VENDING_SHELFS_H_
#define _HONEY_VENDING_SHELFS_H_

#include <stdint.h>

#include "Shift74HC595.h"
#include "config.h"

const uint8_t Shelf1 = 0;
const uint8_t Shelf2 = 1;
const uint8_t Shelf3 = 2;
const uint8_t Shelf4 = 3;
const uint8_t Shelf5 = 4;
const uint8_t Shelf6 = 5;

class Shelf {

  public:
    
    /**
     * Constructor
     * 
     * @param door_shift_register The shift register to control the door locks
     */
    Shelf(const Shift74HC595* const door_shift_register);
    ~Shelf(void);

    /**
     * Set a price for a specific shelf
     *
     * @param shelf_mumber The shelf to set the price from
     * @param shelf_price The price for this shelf
     */
    void set_shelf_price(const uint8_t shelf_number, const uint16_t shelf_price);

    /**
     * Use this function to buy a shelf. If the shelf is full and the amount of money is enough to buy
     * this shelf, it opens, stays open for ten seconds, and closes
     *
     * @param shelf_number The shelf to buy
     * @param money the amount of money to buy the shelf with
     * @return true if buying the shelf was successful, false otherwise
     */
    bool buy_shelf(const uint8_t shelf_number, const uint16_t money);

  private:
    // An array storing the shelf prices 
    uint16_t _shelf_prices[config::SHELF_COUNT];
    // An array to remember which shelf is still full
    bool _is_shelf_full[config::SHELF_COUNT];
    // Instance to the Shelfs shift register to control door locks
    const Shift74HC595* const _door_shift_register;

    // Do not allow copying
    Shelf(const Shelf& other);
    Shelf& operator=(const Shelf& other);
};

#endif
