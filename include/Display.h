#ifndef _HONEY_VENDING_DISPLAY_H_
#define _HONEY_VENDING_DISPLAY_H_

#include <TM1637.h>

// Error Codes
uint16_t TO_MANY_DIGITS_ERROR = 1111;

class Display {

  public:
    Display(const uint8_t clock_pin, const uint8_t data_pin);

    /**
     * Initialize the display
     */
    void init();

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

  private:
    TM1637 _segment_display;
    const uint8_t _max_number_of_digits = 4;

    uint8_t _get_number_of_digits(const uint16_t number);
    uint8_t _get_digit(const uint16_t number, const uint8_t digit);

};

#endif
