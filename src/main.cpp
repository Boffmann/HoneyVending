#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>

// Value of coin refused. For the used Coin Acceptor a value of 255 means that the inserted coin is refused
const int NO_COIN=255;
// enum representing the 8 doors
enum class Door {
door1 = 1,
door2 = 2,
door3 = 3,
door4 = 8,
door5 = 16,
door6 = 32,
door7 = 64,
door8 = 128
};
// enum representing servo rotations
enum class ServoRotations{
// Rotation for the Servo if honey was sold
sold = 0,
// Rotation for the Servo if payment was aborted
aborted = 1
};

// rxPin, txPin
SoftwareSerial coinSerial(2,3);
// The clockPin for shift registers
const int clockPin = 8;
// The dataPin for door shift register
const int dataPin = 9;
// The servoPin to control the coinServo
const int coinServoPin = 7;

// Servo instance to control servo motor that controls coin rocker
Servo coinServo;

/**
 * Sets up all variables for the program
 */
void setup() {
    //Setup Serial Port for Serial Monitor
    Serial.begin(9600);
    Serial.println("Coin Acceptor Ready")
    
    // Setup Serial Port for Coin Acceptor
    coinSerial.begin(4800);

    // Attaches servo connected to coinServoPin to the servo object
    coinServo.attach(coinServoPin);

    // Set PinModes for each individual Pin
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
}

/**
 * opens or closes a specified door
 * @param door The door to open
 * @param doorState The state to set the door to. Either HIGH to open door or LOW to close it
 */
void doorWrite(Door door, int doorState) {
   byte bitsToSend = 0;
   // Convert door to int
   int doorNumber = static_cast<int>(door);

   // Turn on the corresponding bit in bitsToSend
   bitWrite(bitsToSend, doorNumber, doorState);

   // Shift out the bits to open/close door
   shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);
}

/**
 * Rotates the coinServo
 * @param rotation The rotation to rotate the servo at
 */
void moveCoinServo(ServoRotation rotation) {
    //Convert rotation to int
    int rotationValue = static_cast<int>(rotation);
    // Sets the servo position
    coinServo.write(rotationValue);
    // Waits for the Servo to get there
    delay(50);
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
