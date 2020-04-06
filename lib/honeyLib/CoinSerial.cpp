#include "CoinSerial.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

CoinSerial::CoinSerial(void)
  : _current_coin_count{0} {}

void CoinSerial::begin(const uint32_t baud_rate) const {
  Serial.begin(baud_rate);
}

const bool CoinSerial::update(void) {
  int coinValue;

  if (Serial.available()) {
    coinValue = Serial.read();

    if (coinValue != NO_COIN) {
      // The coin collector sends the value of each coin in cents/10
      // e.g. For 2€ it returns 20, for 20 cents it returns 2
      _current_coin_count += (coinValue * 10);
      return true;
    }
  }

  return false;
}

void CoinSerial::reset_coin_count(void) {
  _current_coin_count = 0;
}

uint16_t CoinSerial::get_current_coin_count(void) const {
  return _current_coin_count;
}
