#include "CoinSerial.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

CoinSerial::CoinSerial(void)
  : _current_coin_count{0} {}

void CoinSerial::begin(const uint32_t baud_rate) const {
  Serial.begin(baud_rate);
}

void CoinSerial::update(void) {
  int coinValue;

  if (Serial.available()) {
    coinValue = Serial.read();

    if (coinValue != NO_COIN) {
      _current_coin_count += (coinValue * 10);
    }
  }
}

void CoinSerial::reset_coin_count(void) {
  _current_coin_count = 0;
}

uint16_t CoinSerial::get_current_coin_count(void) const {
  return _current_coin_count;
}
