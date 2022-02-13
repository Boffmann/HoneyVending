#ifndef _HV_SHELFS_INTERFACE_
#define _HV_SHELFS_INTERFACE_

#include <stdint.h>

#include "Shift74HC595.h"
#include "Shelf.h"
#include "OpenShelfList.h"

class ShelfsInterface {

  public:

    ShelfsInterface(uint8_t, uint8_t, uint8_t, uint8_t);

    /**
     * 
     * 
     * @param shelf The shelf to open
     * @return true if the shelf is not empty, false otherwise
     */
    bool buy_shelf(const SHELF_ID, double&);

    /**
     * close shelfs that were open long enough
     * 
     * @return number of closed shelfs
     */
    uint8_t close_overdue_shelfs(void);

    /**
     * For testing purposes only
     */
    OpenShelfList& get_open_shelfs(void);

    /**
     * public because I want it to be tested.
     * In this small project I care more about properly testing my code
     * instead of 100% proper information hiding
     */
    uint8_t open_shelfs_to_bit_mask(void) const;

  private:

    // Instance to the Shelfs shift register to control door locks
    const Shift74HC595 _door_shift_register;

    Shelf _shelfs[MAX_SHELF_ID];
    OpenShelfList _open_shelfs;

    // Do not allow copying
    ShelfsInterface(const ShelfsInterface&);
    ShelfsInterface& operator=(const ShelfsInterface&);

    void _close_shelf(Shelf& shelf) {
      shelf.close();
      this->_open_shelfs.remove(shelf);
      this->_door_shift_register.shift_out(open_shelfs_to_bit_mask());
    }

    bool _should_close(const Shelf& shelf) const {
      return shelf.get_is_open_time() > 30;
    }

    bool _get_shelf_by_id(SHELF_ID shelf_id, Shelf **shelf) {
      if (shelf_id == NO_SHELF) {
        return false;
      }
      *shelf = &_shelfs[shelf_id - 1];
      return true;
    }

};

#endif