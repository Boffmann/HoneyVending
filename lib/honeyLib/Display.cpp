#include "Display.h"

#include "config.h"

Display::Display(const uint8_t clock_pin, const uint8_t data_pin) 
  : _segment_display(clock_pin, data_pin) {}

void Display::init(void) {
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

  uint8_t number_of_digits = get_number_of_digits(number);

  // This display can only show four digits
  if (number_of_digits > config::MAX_DISPLAY_DIGITS) {
    number_of_digits = config::MAX_DISPLAY_DIGITS;
    number = TO_MANY_DIGITS_ERROR;
  }

  // The number of the first segment that is used to show the number
  const uint8_t first_segment_number = config::MAX_DISPLAY_DIGITS - number_of_digits;

  // Display 0 on those parts that do not display anything else to always keep 3 digits
  // lighten up
  for (uint8_t segment_index = 1; segment_index < first_segment_number; ++segment_index) {

    _segment_display.display(segment_index, 0);
  }

  // Get every single digit out of value and display it at proper part of segment display
  for (uint8_t segment_index = first_segment_number; segment_index < config::MAX_DISPLAY_DIGITS; ++segment_index) {
    _segment_display.display(segment_index, get_digit(number, segment_index - first_segment_number));
  }

}

uint8_t Display::get_number_of_digits(uint16_t number) {
  uint8_t result = 0;

  while (number != 0) {
    number /= 10;
    ++result;
  }

  return result;
}

uint8_t Display::get_digit(const uint16_t number, const uint8_t digit) {
  const uint8_t number_of_digits = get_number_of_digits(number);
  const uint8_t digit_difference = number_of_digits - digit - 1;
  const uint16_t divisor = pow(10, digit_difference);

  return (number / divisor) % 10;
}
