#include <Arduino.h>
#include <SoftwareSerial.h>

// Value of coin refused. For the used Coin Acceptor a value of 255 means that the inserted coin is refused
const int NO_COIN=255;
// enum representing the 8 doors
enum class Doors {
door1 = 1,
door2 = 2,
door3 = 3,
door4 = 8,
door5 = 16,
door6 = 32,
door7 = 64,
door8 = 128
};

// rxPin, txPin
SoftwareSerial coinSerial(2,3);
// The clockPin for shift registers
const int clockPin = 8;
// The dataPin for door shift register
const int dataPin = 9;

/**
 * Sets up all variables for the program
 */
void setup() {
    //Setup Serial Port for Serial Monitor
    Serial.begin(9600);
    Serial.println("Coin Acceptor Ready")
    
    // Setup Serial Port for Coin Acceptor
    coinSerial.begin(4800);

    // Set PinModes for each individual Pin
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
}

/**
 * opens or closes a specified door
 * @param doorNumber The Number of the addressed door. Please use enum 'Doors' for this
 * @param doorState The state to set the door to. Either HIGH to open door or LOW to close it
 */
void doorWrite(int doorNumber, int doorState) {
   byte bitsToSend = 0;

   // Turn on the corresponding bit in bitsToSend
   bitWrite(bitsToSend, doorNumber, doorState);

   // Shift out the bits to open door
   shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);
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
