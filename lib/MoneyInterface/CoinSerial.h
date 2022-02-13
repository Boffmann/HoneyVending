#ifndef _COIN_SERIAL_H_
#define _COIN_SERIAL_H_

#include <Arduino.h>

#include <stdint.h>

const uint8_t NO_COIN = 255;

namespace CoinSerial {

    /**
     * Begin serial transmission
     *
     * @param baud_rate The baud rate for this serial transmission
     */
    void begin(const uint32_t baud_rate);

    //See on https://bigdanzblog.wordpress.com/2015/01/12/interfacing-dg600f-coin-acceptor-to-arduino/ for Coin Acceptor Sample Code
    const uint8_t get_inserted_coin();

}


#endif
