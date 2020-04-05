#ifndef _COIN_SERIAL_H_
#define _COIN_SERIAL_H_

#include <Arduino.h>
#include <SoftwareSerial.h>

#include <stdint.h>

const uint16_t NO_COIN = 255;

class CoinSerial {

  public:
    CoinSerial(void);

    /**
     * Begin serial transmission
     *
     * @param baud_rate The baud rate for this serial transmission
     */
    void begin(const uint32_t baud_rate) const;

    /**
     * Reads Serial Input from Coin Acceptor and adds value to _current_coin_count
     * See on https://bigdanzblog.wordpress.com/2015/01/12/interfacing-dg600f-coin-acceptor-to-arduino/ for Coin Acceptor Sample Code
     */
    void update(void);

    /**
     * Resets the coin count. This is invoked when a door was opened
     */
    void reset_coin_count(void);

    /**
     * Return the current coin count
     * @return the current coin count
     */
    uint16_t get_current_coin_count(void) const;

  private:

      // current amount of coins inserted
      uint16_t _current_coin_count;
      
};

#endif
