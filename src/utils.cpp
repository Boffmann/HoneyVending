#include "utils.h"
#include "config.h"

namespace utils {
    uint8_t shiftIn(const int dataPin, const int clockPin){

        int tmpButtonState = 0;
        uint8_t pressedButton = 0;

        // Loop over all door buttons. Register transmits information about pins from pin 7 to
        // pin 0. So the lsrc/utils.cpp:16:34:oop counts down
        for (int i = config::shelfCount - 1; i >= 0; i--) {
            // A low to high clock drop causes the shift register's data pin to change state based
            // on value of the next bit in its serial information flow
            digitalWrite(clockPin, LOW);
            delayMicroseconds(0.2);
            tmpButtonState = digitalRead(dataPin);
            if (tmpButtonState) {
                // the button at i was pressed and is stored in pressedButtons byte as bit at i                
                pressedButton = pressedButton | (1 << i);
            }
            digitalWrite(clockPin, HIGH);
        }

        return pressedButton;
    }

}