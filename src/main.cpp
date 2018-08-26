#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <TM1637.h>

#include "config.h"
#include "utils.h"


SoftwareSerial coinSerial(config::coinRX, config::coinTX);
const int buttonResetPin = config::buttonResetPin;
const int buttonAbortPin = config::buttonAbortPin;
const int latchPin = config::latchPin;
const int clockPin = config::clockPin;
const int dataPinDoor = config::dataPinDoor;
const int dataPinDisplay = config::dataPinDisplay;
const int dataPinInput = config::dataPinInput;
const int coinServoPin = config::coinServoPin;
TM1637 segmentDisplay(clockPin, dataPinDisplay);

// Servo instance to control servo motor that controls coin rocker
Servo coinServo;

// The current state of the vending mashine
config::State state = config::State::IDLE;

// The currently selected honey shelf
int selectedShelf = config::NO_SHELF;
int leftToPay = 500;

// Array representing if shelf at position is filled or not
bool shelfFilled[config::shelfCount];


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

    // Initialize 7-segment-display and set its brightness
    segmentDisplay.init();
    segmentDisplay.set(BRIGHT_TYPICAL);

    // Set PinModes for each individual Pin
    pinMode(buttonResetPin, INPUT);
    pinMode(buttonAbortPin, INPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPinDoor, OUTPUT);
    pinMode(dataPinDisplay, OUTPUT);
    pinMode(dataPinInput, INPUT);
    pinMode(coinServoPin, OUTPUT);

    //Debug purpose only
    pinMode(13, OUTPUT);

    // Init with all shelfs filled
    for(int i = 0; i < config::shelfCount; ++i) {
        shelfFilled[i] = true;
    }
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

/**
 * Shows a digit on the display
 * @param value the digit to show
 * @param strangeMode there is something strange happening when passing integer
 * variables in this method. The divisor is 9 instead of 10???
 * Only happens when somewhere in code this integer changes.
 * When this functions shows something weird, try strangeMode off
 */
void display(int value, bool strangeMode = true) {

    int strangeAdd = 0;
    if (strangeMode) {
        strangeAdd = 1;
    }

    // Do not display values that are less than zero
    if (value < 0) {
        value = 0;
    }

    int numDigits = utils::countNumberOfDigits(value);

    // If value is bigger than the display can view, return
    if (numDigits > config::MAX_DISPLAY_FIELDS) {
        Serial.print("Number of digits is to high. Value was: ");
        Serial.println(value);
        return;
    }

    // This does some very strange behaviour. That is why +1 at the end
    int divisor = static_cast<int>(pow(10, numDigits - 1)) + strangeAdd;
    
    // Activate points on display
    segmentDisplay.point(POINT_ON);

    // Display 0 on those parts that do not display anything else to always keep 3 digit lighten up
    for (int i = 1; i < config::MAX_DISPLAY_FIELDS - numDigits; ++i) {
        segmentDisplay.display(i, 0);
    }

    // Get every single digit out of value and display it at proper part of segment display
    for( int i = 0; i < numDigits; i++) {
        segmentDisplay.display(config::MAX_DISPLAY_FIELDS - numDigits + i, value / divisor);
        /*Serial.print("value: ");
        Serial.println(value);
        Serial.print("Divisor: ");
        Serial.println(divisor);
        Serial.println(value / divisor);*/
        value = value % divisor;
        divisor = divisor / 10;
    }
}

/**
 * Determines the pressed button
 * @return button Code of the pressed button
 */
int getButtonPressed() {
    
    // Check reset Button pressed
    if (digitalRead(buttonResetPin)) {
        return config::BUTTON_RESET;
    }
    //Check abort button pressed
    if (digitalRead(buttonAbortPin)){
        return config::BUTTON_ABORT;
    }

    // Do not allow to get a honey button pressed when this is not allowed
    if (state != config::State::PAYED) {
        return config::NO_BUTTON_PRESSED;
    }

    // set latch to LOW to collect parallel data
    digitalWrite(latchPin, LOW);
    // Wait for data to get collected
    delayMicroseconds(20);
    // Set latch to HIGH to transmit data serially
    digitalWrite(latchPin, HIGH);

    uint8_t bitFieldButtonPressed = shiftIn(dataPinInput, clockPin, MSBFIRST);
    
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
    state = config::State::COLLECTING;
    selectedShelf = config::NO_SHELF;

    // Reset all shelfs to filled
    for(int i = 0; i < config::shelfCount; ++i) {
        shelfFilled[i] = true;
    }
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
            state = config::State::COLLECTING;
            break;
        case config::State::COLLECTING:
            display(leftToPay, false);
            break;
    }
    

    // Handle button reset and abort with special treatment
    if (pressedButton == 1) {
        digitalWrite(13, HIGH);
    } else {
        digitalWrite(13, LOW);
    }

}
