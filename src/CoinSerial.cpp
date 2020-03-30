#include "CoinSerial.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

CoinSerial::CoinSerial(const uint8_t rx, const uint8_t tx, const uint32_t boud_rate = 4800)
  : _current_coin_count{0},
    _software_serial{rx, tx} {
      _software_serial.begin(boud_rate);
    }

CoinSerial::update() {
  int coinValue;

  if (_software_serial.available()) {
    coinValue = coinSerial.read();

    if (coinValue != NO_COIN) {
      _current_coin_count += coinValue;
    }
  }
}

CoinSerial::reset_coin_count() {
  _current_coin_count = 0;
}

CoinSerial::get_current_coin_count() const {
  return _current_coin_count;
}
