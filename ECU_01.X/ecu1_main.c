#include "adc.h"
#include "can.h"
#include "ecu1_sensor.h"
#include "msg_id.h"
#include "uart.h"
#include "matrix_keypad.h"
#include "clcd.h"

static void init_config(void) {
    init_adc();
    init_matrix_keypad();
    init_clcd();
    init_can();
}

int main(void) {
    init_config();

    while (1) {
        clcd_print("SPEED   ", LINE1(0));
        clcd_print("GEAR    ", LINE1(8));

        get_speed(); // Read speed
        get_gear_pos(); // Read gear
    }

    return 0;
}