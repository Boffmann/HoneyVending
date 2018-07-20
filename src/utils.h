#ifndef _HONEY_VENDING_UTILS_H_
#define _HONEY_VENDING_UTILS_H_

#include <Arduino.h>
#include "config.h"
namespace utils {
    
    /**
     * Counts the digits of a number
     * @param i the number to count the digits from
     * @ return number of digits of i
     */
    int countNumberOfDigits(int i);
}

#endif