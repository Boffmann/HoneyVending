#ifndef _HONEY_VENDING_SHELFS_H_
#define _HONEY_VENDING_SHELFS_H_

#include <stdint.h>

#include "Hardware/Shift74HC595.h"
#include "Data/Shelf.h"
#include "Data/OpenShelfList.h"
#include "config.h"


const uint8_t SHELF_COUNT = 6;

class ShelfsInterface {

  public:

    // TODO Implement constructor
    ShelfsInterface();

    void add_shelf(const SHELF, const uint32_t);

    /**
     * Use this function to queue a shelf to open. If the shelf is empty, it will not be queued
     * 
     * @param shelf The shelf to open
     * @return true if the shelf is not empty, false otherwise
     */
    const bool buy_shelf(const SHELF, uint32_t&);

    /**
     * close shelfs that were open long enough
     */
    void close_overdue_shelfs(void); 

  private:

    Shelf _shelfs[SHELF_COUNT];
    /** counter to track how many timer interrupts were registered to close doors again */
    uint8_t _passed_timers;
    OpenShelfList _open_shelfs;

    // Instance to the Shelfs shift register to control door locks
    const Shift74HC595 _door_shift_register;

    // Do not allow copying
    ShelfsInterface(const ShelfsInterface&);
    ShelfsInterface& operator=(const ShelfsInterface&);

    void _close_shelf(Shelf&);
    // TODO Implementation
    const bool _should_close(const Shelf&) const;

};

#endif
