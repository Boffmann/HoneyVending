#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial coinSerial(2,3);

void setup() {
    Serial.begin(9600);
    Serial.println("Coin Acceptor Ready")
    
    coinSerial.begin(4800);

    pinMode(13, OUTPUT);
}

void loop() {
    int coinValue;
   
    // Check if signal is coming from coin acceptor
    if (coinSerial.available()) {
        // Read Value from Coin acceptor
        coinValue = coinSerial.read();

        // Coin Value of 255 means coin refused
        if (coinValue != 255) {
                // Print value
                Serial.print("Coin accepted. Value is:");
                Serial.println(coinValue);
        }
    } 
}
