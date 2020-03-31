#include "CoinSerial.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

CoinSerial::CoinSerial(const std::unique_ptr<SerialWrapper> serial)
  : _current_coin_count{0},
    _serial{std::move(serial)} {
      _software_serial.begin(boud_rate);
    }

CoinSerial::begin() {
  _serial->begin();
}

CoinSerial::update() {
  int coinValue;

  if (_serial->available()) {
    coinValue = _serial->read();

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
