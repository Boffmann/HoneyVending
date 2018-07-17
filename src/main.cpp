#include <Arduino.h>
#include <SoftwareSerial.h>

// Value of coin refused. For the used Coin Acceptor a value of 255 means that the inserted coin is refused
const int NO_COIN=255;

// rxPin, txPin
SoftwareSerial coinSerial(2,3);

/**
 * Sets up all variables for the program
 */
void setup() {
    //Setup Serial Port for Serial Monitor
    Serial.begin(9600);
    Serial.println("Coin Acceptor Ready")
    
    // Setup Serial Port for Coin Acceptor
    coinSerial.begin(4800);

    pinMode(13, OUTPUT);
}

/**
 * Reads Serial Input from the Coin Accrptor and returns value of inserted Coin 
 * See on https://bigdanzblog.wordpress.com/2015/01/12/interfacing-dg600f-coin-acceptor-to-arduino/ for Coin Acceptor Sample Code
 * @return Coin Value if Coin is inserted, NO_COIN instead
 */
int getInsertedCoin() {
    int coinValue;
   
    // Check if signal is coming from coin acceptor
    if (coinSerial.available()) {
        // Read Value from Coin acceptor
        coinValue = coinSerial.read();

        // Coin Value of 255 means coin refused
        if (coinValue != NO_COIN) {
                // Print value
                Serial.print("Coin accepted. Value is:");
                Serial.println(coinValue);
                return coinValue
        }
    } 
    return NO_COIN;
}

/**
 * Main loop routine
 */
void loop() {

}
