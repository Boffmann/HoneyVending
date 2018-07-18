#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>

#include "config.h"


SoftwareSerial coinSerial(config::coinRX, config::coinTX);
const int buttonResetPin = config::buttonResetPin;
const int buttonAbortPin = config::buttonAbortPin;
const int latchPin = config::latchPin;
const int clockPin = config::clockPin;
const int dataPinDoor = config::dataPinDoor;
const int dataPinButtons = config::dataPinButtons;
const int coinServoPin = config::coinServoPin;

// Servo instance to control servo motor that controls coin rocker
Servo coinServo;

/**
 * Sets up all variables for the program
 */
void setup() {
    //Setup Serial Port for Serial Monitor
    Serial.begin(9600);
    Serial.println("Coin Acceptor Ready");
    
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

    //Debug purpose only
    pinMode(13, OUTPUT);
}

/**
 * opens or closes a specified door
 * @param door The door to open
 * @param doorState The state to set the door to. Either HIGH to open door or LOW to close it
 */
void doorWrite(int door, int doorState) {
   byte bitsToSend = 0;
   // Convert door to int
   int doorNumber = config::doorBytes[door];

   // Turn on the corresponding bit in bitsToSend
   bitWrite(bitsToSend, doorNumber, doorState);

   // Shift out the bits to open/close door
   shiftOut(dataPinDoor, clockPin, MSBFIRST, bitsToSend);
}

/**
 * Rotates the coinServo
 * @param rotation The rotation to rotate the servo at
 */
void moveCoinServo(config::ServoRotations rotation) {
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
        return config::BUTTON_RESET;
    }
    //Check abort button pressed
    if (digitalRead(buttonAbortPin)){
        return config::BUTTON_ABORT;
    }

    // set latch to LOW to collect parallel data
    digitalWrite(latchPin, LOW);
    // Wait for data to get collected
    delayMicroseconds(20);
    // Set latch to HIGH to transmit data serially
    digitalWrite(latchPin, HIGH);

    // Loop over all door buttons. Register transmits information about pins from pin 7 to
    // pin 0. So the loop counts down
    for (int i = config::doorNumbers - 1; i >=0; i--) {
        // A low to high clock drop causes the shift register's data pin to change state based
        // on value of the next bit in its serial information flow
        digitalWrite(clockPin, LOW);
        delayMicroseconds(0.2);
        tmpButtonState = digitalRead(dataPinButtons);
        if (tmpButtonState) {
            // At this point, a door button was pressed
            pressedButton |= (1 << i);
            return i; // pressedButton is binary representation
        }
        digitalWrite(clockPin, HIGH);
    }
    return config::NO_BUTTON_PRESSED;
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
        if (coinValue != config::NO_COIN) {
                // Print value
                Serial.print("Coin accepted. Value is:");
                Serial.println(coinValue);
                return coinValue;
        }
    } 
    return config::NO_COIN;
}



/**
 * Main loop routine
 */
void loop() {
    // Add a delay between each loop of 1/10th of a second to give the system some downtime
    delay(100);
    // First of all, get if a button is pressed
    int pressedButton = getButtonPressed();
    if (pressedButton == config::NO_BUTTON_PRESSED) {
        return;
    }

    // Handle button reset and abort with special treatment
    if (pressedButton == 1) {
        digitalWrite(13, HIGH);
    } else {
        digitalWrite(13, LOW);
    }

}
