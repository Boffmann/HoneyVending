#ifndef _HV_CONFIG_H
#define _HV_CONFIG_H

#include <stdint.h>

namespace config {

    // Pin numbers
    const uint8_t reset_button = 2;
    const uint8_t coin_rx = 3;
    const uint8_t button_shift_load = 4;
    const uint8_t button_clock = 5;
    const uint8_t button_output = 6;
    const uint8_t segment_signal = 7;
    const uint8_t segment_clock = 8;
    const uint8_t door_output = 9;
    const uint8_t door_storage_register_clock = 10;
    const uint8_t door_shift_register_clock = 11;
    const uint8_t door_output_enable = 12;
    const uint8_t coin_tx = 13;

    const uint8_t button_rack_interrupt = 14;

}

#endif
