#ifndef _HONEY_VENDING_UTILS_H_
#define _HONEY_VENDING_UTILS_H_

#include <Arduino.h>
#include "config.h"
namespace utils {
    /**
     * Shifts in data from a PISO shift register
     * @param dataPin the dataPin where the load pin from PISO SR is connected to
     * @param clockPin the clockPin where the clock pin from PISO SR is connected to 
     */
    byte shiftIn(const int dataPin, const int clockPin);
}

#endif