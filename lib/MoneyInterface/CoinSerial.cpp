#include "CoinSerial.h"

#include <Arduino.h>
#include <HardwareSerial.h>


// TODO Use Hardware Serial
void CoinSerial::begin(const uint32_t baud_rate) {
  Serial.begin(baud_rate);
}

const uint8_t CoinSerial::get_inserted_coin() {
  int coinValue;

  if (Serial.available()) {
    coinValue = Serial.read();

    if (coinValue != NO_COIN) {
      // The coin collector sends the value of each coin in cents/10
      // e.g. For 2€ it returns 20, for 20 cents it returns 2
      return coinValue * 10;
    }
  }

  return NO_COIN;
}
