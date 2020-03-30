#ifndef _HONEY_VENDING_SHELFS_H_
#define _HONEY_VENDING_SHELFS_H_

#include <vector>

#include "74HC595.h"

const uint8_t Shelf1 = 0,
const uint8_t Shelf2 = 1,
const uint8_t Shelf3 = 2,
const uint8_t Shelf4 = 3,
const uint8_t Shelf5 = 4,
const uint8_t Shelf6 = 5;

class Shelfs {

  public:
    Shelfs(const uint8_t shelf_count, std::unique_ptr<74HC595> door_shift_register);

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
    boolean buy_shelf(const uint8_t shelf_number, const uint16_t money);

  private:
    const uint8_t _shelf_count;
    std::vector<uint16_t> _shelf_prices;
    std::vector<boolean> _is_shelf_full;
    std::unique_ptr<74HC595> _door_shift_register;
};

#endif
