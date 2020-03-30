#ifndef _COIN_SERIAL_H_
#define _COIN_SERIAL_H_

const uint16_t NO_COIN = 255;

class CoinSerial {

  public:
    CoinSerial(const uint8_t rx, const uint8_t tx, const uint32_t boud_rate);

    /**
     * Reads Serial Input from Coin Acceptor and adds value to _current_coin_count
     * See on https://bigdanzblog.wordpress.com/2015/01/12/interfacing-dg600f-coin-acceptor-to-arduino/ for Coin Acceptor Sample Code
     */
    void update();

    /**
     * Resets the coin count. This is invoked when a door was opened
     */
    void reset_coin_count();

    /**
     * Return the current coin count
     * @return the current coin count
     */
    uint16_t get_current_coin_count() const;

  private:
      uint16_t _current_coin_count;
      SoftwareSerial _software_serial;

};

#endif
