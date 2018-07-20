#ifndef _HONEY_VENDING_CONFIG_H_
#define _HONEY_VENDING_CONFIG_H_

namespace config {

    // Value of coin refused. For the used Coin Acceptor a value of 255 means that the inserted coin is refused
    const int NO_COIN=255;

    // All states of the vending mashine
    enum State {IDLE, COLLECTING, PAYED, ABORTING};

    // Number of Doors
    const int shelfCount = 8;
    // Array to map door numbers to correct byte for shiftout
    const int doorBytes[shelfCount] = { 1, 2, 4, 8, 16, 32 ,64 ,128 };

    // Button Values
    const int NO_BUTTON_PRESSED = -1;
    const int BUTTON_RESET = -2;
    const int BUTTON_ABORT = -3;

    // Shelf Values
    const int NO_SHELF = -1;

    // Maximal Display Fields
    const int MAX_DISPLAY_FIELDS = 4;

    // Prices for each shelf
    const int shelfPrices[shelfCount] = {
        500, // Shelf 1
        500, // Shelf 2
        500, // Shelf 3
        500, // Shelf 4
        500, // Shelf 5
        500, // Shelf 6
        500, // Shelf 7
        500  // Shelf 8
    };
    

    //------------------------------
    // Pin numbers
    // rxPin, txPin for coinAcceptor
    const int coinRX = 4, coinTX = 5;
    // The pin to get reset Button pressed
    const int buttonResetPin = 6;
    // The pin to get abort button pressed
    const int buttonAbortPin = 7;
    // The latch pin for shift registers
    const int latchPin = 8;
    // The clockPin for shift registers
    const int clockPin = 9;
    // The dataPin for door shift register
    const int dataPinOutput = 10;
    // The dataPin for buttons shift register
    const int dataPinInput = 11;
    // The servoPin to control the coinServo
    const int coinServoPin = 12;
    //------------------------------

    // enum representing servo rotations
    enum class ServoRotations{
    // Rotation for the Servo if honey was sold
    sold = 0,
    // Rotation for the Servo if payment was aborted
    aborted = 1
    };


}

#endif