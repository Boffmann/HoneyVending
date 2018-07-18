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

// The current state of the vending mashine
config::State state = config::State::IDLE;

// The currently selected honey shelf
int selectedShelf = config::NO_SHELF;
int leftToPay = 0;

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
    
    // Check reset Button pressed
    if (digitalRead(buttonResetPin)) {
        return config::BUTTON_RESET;
    }
    //Check abort button pressed
    if (digitalRead(buttonAbortPin)){
        return config::BUTTON_ABORT;
    }

    if (state != config::State::IDLE) {
        return config::NO_BUTTON_PRESSED;
    }

    // set latch to LOW to collect parallel data
    digitalWrite(latchPin, LOW);
    // Wait for data to get collected
    delayMicroseconds(20);
    // Set latch to HIGH to transmit data serially
    digitalWrite(latchPin, HIGH);

    uint8_t bitFieldButtonPressed = shiftIn(dataPinButtons, clockPin, MSBFIRST);
    
    for (int i = 0; i < config::shelfCount; i++) {
        if (bitFieldButtonPressed & (1 << i)) {
            return i;
        }
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
 * Resets the complete mashine 
 */
void resetMashine() {
    state = config::State::IDLE;
    selectedShelf = config::NO_SHELF;
}

/**
 * Main loop routine
 */
void loop() {
    // Add a delay between each loop of 1/10th of a second to give the system some downtime
    delay(300);
    
    // First of all, get if a button is pressed
    int pressedButton = getButtonPressed();
    Serial.print("Button:");
    Serial.println(pressedButton);

    // Switch over state to execute state specific operations
    switch (state) {
        case config::State::IDLE:
            // If in Idle state no button is pressed, the mashine gets no new task
            if (pressedButton == config::NO_BUTTON_PRESSED) {
                return;
            }
            if (pressedButton == config::BUTTON_RESET) {
                resetMashine();
                return;
            }
            if (pressedButton == config::BUTTON_ABORT) {
                state = config::State::ABORTING;
                return;
            }
            selectedShelf = pressedButton;
            leftToPay = config::shelfPrices[selectedShelf];
            state = config::State::PAYING;
            break;
        case config::State::PAYING:
            // TODO
            break;
    }
    

    // Handle button reset and abort with special treatment
    if (pressedButton == 1) {
        digitalWrite(13, HIGH);
    } else {
        digitalWrite(13, LOW);
    }

}
