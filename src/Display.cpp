#include "Display.h"

Display::Display(const uint8_t clock_pin, const uint8_t data_pin) 
  : _segment_display(clock_pin, data_pin) {}

void Display::init() {
  _segment_display.init();
  _segment_display.point(POINT_ON);
}

void Display::set_brightness(const uint8_t brightness) {
  _segment_display.set(brightness);
}

void Display::show(uint16_t number) {


  if (number < 0) {
    number = 0;
  }

  if (number > 9999) {
    number = 9999;
  }

  uint8_t number_of_digits = _get_number_of_digits(number);

  // This display can only show four digits
  if (number_of_digits > _max_number_of_digits) {
    number_of_digits = _max_number_of_digits;
    number = TO_MANY_DIGITS_ERROR;
  }

  // Display 0 on those parts that do not display anything else to always keep 3 digits
  // lighten up
  for (uint8_t segment_index = 1; segment_index < _max_number_of_digits - number_of_digits; ++segment_index) {

    _segment_display.display(segment_index, 0);
  }

  // Get every single digit out of value and display it at proper part of segment display
  for (uint8_t segment_index = 3; segment_index >= 0; --segment_index) {
    _segment_display.display(segment_index, _get_digit(number, segment_index));
  }

}


uint8_t Display::_get_number_of_digits(uint16_t number) {
  uint8_t result = 0;

  while (number != 0) {
    number /= 10;
    ++result;
  }

  return result;
}

uint8_t Display::_get_digit(const uint16_t number, const uint8_t digit) {
  switch (digit) {
    case 0:
      return number / 1000 % 10;
    case 1:
      return number / 100 % 10;
    case 2:
      return number / 10 % 10;
    case 3:
      return number % 10;
    default:
      return 8;
  }
}
