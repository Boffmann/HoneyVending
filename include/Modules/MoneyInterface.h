#ifndef _MONEY_INTERFACE_H_
#define _MONEY_INTERFACE_H_

#include "Hardware/CoinSerial.h"
#include "Hardware/Display.h"

#include <stdint.h>

class MoneyInterface {

public:

    MoneyInterface();

    /**
     * Reads money transfer from all connected money sources and updates the display
     * 
     * @return true if new coin was inserted, false otherwise
     */
    const void update(void);

    /**
     * Returns current money balance
     */
    const uint32_t get_balance(void) const;

    /**
     * Notify the money interface that money has been spent
     * 
     * @param amount The amount of money spent
     */
    const void money_spend(const uint32_t amount);

private:

    uint32_t _balance;
    // Do not allow copying
    ButtonRack(const ButtonRack& other);
    ButtonRack& operator=(const ButtonRack& other);

};

#endif