#include "utils.h"
#include "config.h"

namespace utils {
    
    int countNumberOfDigits(int i) {
        int result = 0;

        while(i != 0) {
            i /= 10;
            ++result;
        }

        return result;
    }

}