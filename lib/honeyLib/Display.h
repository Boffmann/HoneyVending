#ifndef _HONEY_VENDING_DISPLAY_H_
#define _HONEY_VENDING_DISPLAY_H_

#include <lib/DigitalTube/TM1637.h>

#include "config.h"

	
// Error Codes
const uint16_t TO_MANY_DIGITS_ERROR = 1111;

class Display {

  public:

    /**
     * Constructor
     *
     * @param clock_pin The segment display's clock pin
     * @param data_pin The segment display's data pin
     */
    Display(const uint8_t clock_pin, const uint8_t data_pin);

    /**
     * Initialize the display
     */
    void init(void);

    /**
     * Set the display's brightness
     *
     * @param brightness The brightness to set
     */
    void set_brightness(const uint8_t brightness);

    /**
     * Show a number on the display
     *
     * @param number The number to show
     */
    void show(uint16_t number);

    /**
     * Clear the display
     */
    void clear(void);

    /**
     * Helper function to get the numbers of digits of a number
     * e.g. number of digits of 23 is 2 and of 1234 is 4
     *
     * @param number Number to get the digit count from
     * @return The amount of digits in the number
     */
    const uint8_t get_number_of_digits(const uint16_t number) const;

    /**
     * Helper function to get the digit at a specific location
     *
     * @param number The number to get the digit from
     * @param digit The digit number to get
     * @return The digit at the desired location
     */
    const uint8_t get_digit(const uint16_t number, const uint8_t digit) const;

  private:
    // Actual segment instance
    TM1637 _segment_display;

};

#endif
