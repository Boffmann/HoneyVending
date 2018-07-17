#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>

// Value of coin refused. For the used Coin Acceptor a value of 255 means that the inserted coin is refused
const int NO_COIN=255;
// Value of no button pressed
const int NO_BUTTON_PRESSED = -1;
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

// Number of Doors
const int doorNumbers = 8;

// rxPin, txPin
SoftwareSerial coinSerial(2,3);
// The pin to get reset Button pressed
const int buttonResetPin = 5;
// The pin to get abort button pressed
const int buttonAbortPin = 6;
// The latch pin for shift registers
const int latchPin = 7;
// The clockPin for shift registers
const int clockPin = 8;
// The dataPin for door shift register
const int dataPinDoor = 9;
// The dataPin for buttons shift register
const int dataPinButtons = 10;
// The servoPin to control the coinServo
const int coinServoPin = 11;

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
    pinMode(buttonResetPin, INPUT);
    pinMode(buttonAbortPin, INPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPinDoor, OUTPUT);
    pinMode(dataPinButtons, INPUT);
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

int getButtonPressed() {
    int tmpButtonState = 0;
    int pressedButton = 0;
    
    // Check reset Button pressed
    if (digitalRead(buttonResetPin)) {
        // TODO Return buttonReset
        return 0;
    }
    //Check abort button pressed
    if (digitalRead(buttonAbortPin)){
        // TODO Return buttonAbort
        return 0;
    }

    // set latch to LOW to collect parallel data
    digitalWrite(latchPin, LOW);
    // Wait for data to get collected
    delayMicroseconds(20);
    // Set latch to HIGH to transmit data serially
    digitalWrite(latchPin, HIGH);

    // Loop over all door buttons. Register transmits information about pins from pin 7 to
    // pin 0. So the loop counts down
    for (int i = doorNumbers - 1; i >=0; i--) {
        // A low to high clock drop causes the shift register's data pin to change state based
        // on value of the next bit in its serial information flow
        digitalWrite(clockPin, LOW);
        delayMicroseconds(0.2);
        tmpButtonState = digitalRead(dataPinButtons);
        if (tmpButtonState) {
            // At this point, a door button was pressed
            pressedButton |= (1 << i);
            return resultDataIn;
        }
        digitalWrite(clockPin, HIGH);
    }
    return NO_BUTTON_PRESSED;
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
