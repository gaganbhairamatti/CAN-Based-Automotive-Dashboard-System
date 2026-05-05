#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include "matrix_keypad.h"
#include "clcd.h"

uint16_t adc_val;
uint16_t speed;

uint8_t speed_arr[3];
uint8_t gear_arr[3];

char key;
char value;

unsigned char speed_rec[3];
unsigned char speed_len;
unsigned short speed_msg_id;

unsigned char gear_rec[3];
unsigned char gear_len;
unsigned short gear_msg_id;

static char index = 0;

char gear[9][3] = {"ON", "GN", "G1", "G2", "G3", "G4", "G5", "GR", "CL"};

uint16_t get_speed() {
    // Implement the speed function

    adc_val = read_adc(CHANNEL4); // Read ADC value
    speed = adc_val / 10.23; // Convert ADC to speed

    // Store speed in character array
    speed_arr[0] = (speed / 10) + '0';
    speed_arr[1] = (speed % 10) + '0';
    speed_arr[2] = '\0';

    // Display local speed
    clcd_putch(speed_arr[0], LINE2(5));
    clcd_putch(speed_arr[1], LINE2(6));

    // Transmit speed over CAN
    can_transmit(SPEED_MSG_ID, speed_arr, 2);
    __delay_ms(80);

    // Receive speed from another ECU
//    can_receive(&speed_msg_id, speed_rec, &speed_len);
    
//    speed_rec[2] = '\0';
    // Display received speed
//    clcd_print(speed_rec, LINE2(0));
    //    clcd_putch(speed_rec[0], LINE2(0));
    //    clcd_putch(speed_rec[1], LINE2(1));

    return speed;
}

unsigned char get_gear_pos() {
    // Implement the gear function

    key = scan_switch(); // Scan keypad
    value = triggering_type(EDGE, key); // Edge detection

    if (value == KEY_1) {
        if (index < 7) {
            index++;
        }
    } else if (value == KEY_4) {
        if (index > 0) {
            index--;
        }
    } else if (value == KEY_7) {
        index = 8;
    }

    // Store selected gear
    gear_arr[0] = gear[index][0];
    gear_arr[1] = gear[index][1];
    gear_arr[2] = '\0';

    // Display local gear
    clcd_print(gear_arr, LINE2(8));

    // Transmit gear over CAN
    can_transmit(GEAR_MSG_ID, gear_arr, 2);
    __delay_ms(80);

    // Receive gear from another ECU
//    can_receive(&gear_msg_id, gear_rec, &gear_len);
    
//    gear_rec[2] = '\0';

    // Display received gear
//    clcd_print(gear_rec, LINE2(12));
    //    clcd_putch(gear_rec[0], LINE2(12));
    //    clcd_putch(gear_rec[1], LINE2(13));

    return 0;
}