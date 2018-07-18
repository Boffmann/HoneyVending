namespace config {

    // Value of coin refused. For the used Coin Acceptor a value of 255 means that the inserted coin is refused
    const int NO_COIN=255;

    // Number of Doors
    const int doorNumbers = 8;
    // Array to map door numbers to correct byte for shiftout
    int doorBytes[doorNumbers] = { 1, 2, 4, 8, 16, 32 ,64 ,128 };

    // Button Values
    const int NO_BUTTON_PRESSED = -1;
    const int BUTTON_RESET = -2;
    const int BUTTON_ABORT = -3;
    

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
    const int dataPinDoor = 10;
    // The dataPin for buttons shift register
    const int dataPinButtons = 11;
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