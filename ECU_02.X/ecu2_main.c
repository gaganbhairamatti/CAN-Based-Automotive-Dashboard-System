#include "adc.h"
#include "can.h"
#include "ecu2_sensor.h"
#include "msg_id.h"
#include "uart.h"
#include "matrix_keypad.h"
#include "clcd.h"
#include "ssd_display.h"
#include "digital_keypad.h"

void init_led();

static void init_config(void) {
    init_adc();
    init_ssd_control();
    init_led();
    init_digital_keypad();
    init_can();
}

int main() {

    init_config();
    //call the functions
    while (1) {
        get_rpm();
        process_indicator();
    }
}

void init_led() {
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;
}
