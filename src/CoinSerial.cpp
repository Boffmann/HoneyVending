#include "CoinSerial.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

CoinSerial::CoinSerial()
  : _current_coin_count{0} {}

void CoinSerial::begin(const uint32_t baud_rate) const {
  Serial.begin(baud_rate);
}

void CoinSerial::update() {
  int coinValue;

  if (Serial.available()) {
    coinValue = Serial.read();

    if (coinValue != NO_COIN) {
      _current_coin_count += coinValue;
    }
  }
}

void CoinSerial::reset_coin_count() {
  _current_coin_count = 0;
}

uint16_t CoinSerial::get_current_coin_count() const {
  return _current_coin_count;
}