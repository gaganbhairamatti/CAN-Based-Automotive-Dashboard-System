#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"
#include "isr.h"

//volatile unsigned char led_state = LED_OFF, status = e_ind_off;

unsigned char rx_data[8];
unsigned char rx_len;
unsigned short rx_msg_id;
IndicatorStatus status_rx;

void handle_speed_data(uint8_t *data, uint8_t len) {
    //Implement the speed function
    data[2] = '\0';
    clcd_print(data, LINE2(0));
}

void handle_gear_data(uint8_t *data, uint8_t len) {
    //Implement the gear function
    data[2] = '\0';
    clcd_print(data, LINE2(4));
}

void handle_rpm_data(uint8_t *data, uint8_t len) {
    //Implement the rpm function
    data[4] = '\0';
    clcd_print(data, LINE2(9));
}

void handle_engine_temp_data(uint8_t *data, uint8_t len) {
    //Implement the temperature function
}

void handle_indicator_data(uint8_t *data, uint8_t len) {
    //Implement the indicator function

    status_rx = (IndicatorStatus) data[0];

    if (status_rx == e_ind_off) {
        clcd_print("  ", LINE2(13));

        PORTBbits.RB0 = 0;
        PORTBbits.RB1 = 0;
        PORTBbits.RB6 = 0;
        PORTBbits.RB7 = 0;
    } else if (status_rx == e_ind_left) {
        clcd_print("<-", LINE2(13));

        if (blink_flag) {
            PORTBbits.RB0 = 1;
            PORTBbits.RB1 = 1;
        } else {
            PORTBbits.RB0 = 0;
            PORTBbits.RB1 = 0;
        }

        PORTBbits.RB6 = 0;
        PORTBbits.RB7 = 0;
    } else if (status_rx == e_ind_right) {
        clcd_print("->", LINE2(13));

        if (blink_flag) {
            PORTBbits.RB6 = 1;
            PORTBbits.RB7 = 1;
        } else {
            PORTBbits.RB6 = 0;
            PORTBbits.RB7 = 0;
        }

        PORTBbits.RB0 = 0;
        PORTBbits.RB1 = 0;
    }
}

void process_canbus_data() {
    //process the CAN bus data

    can_receive(&rx_msg_id, rx_data, &rx_len);
    if (rx_len == 0) return;

    if (rx_msg_id == SPEED_MSG_ID) {
        handle_speed_data(rx_data, rx_len);
    } else if (rx_msg_id == GEAR_MSG_ID) {
        handle_gear_data(rx_data, rx_len);
    } else if (rx_msg_id == RPM_MSG_ID) {
        handle_rpm_data(rx_data, rx_len);
    } else if (rx_msg_id == INDICATOR_MSG_ID) {
        handle_indicator_data(rx_data, rx_len);
    }
}

