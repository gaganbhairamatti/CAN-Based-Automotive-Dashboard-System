/*
 * File:   ecu1_sensor.c
 * Author: Omkar
 *
 * Created on 1 April, 2026, 1:08 PM
 */

#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include "ssd_display.h"
#include "clcd.h"
#include "digital_keypad.h"

int count_r;
int count_l;

uint16_t adc_val;
uint16_t rpm;

unsigned char rpm_arr[5];
unsigned char digit[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
unsigned char ssd[4];
unsigned char key;

unsigned char rpm_rec[5];
unsigned char rpm_len;
unsigned short rpm_msg_id;

unsigned char ind_tx[1];
unsigned char ind_rx[1];
unsigned char ind_len;
unsigned short ind_msg_id;
IndicatorStatus status = e_ind_off;
IndicatorStatus status_rx;

uint16_t get_rpm(void) {
    adc_val = read_adc(CHANNEL4);

    rpm = ((adc_val / 10.23) * 60);

    rpm_arr[0] = (rpm / 1000) + '0';
    rpm_arr[1] = ((rpm / 100) % 10) + '0';
    rpm_arr[2] = ((rpm / 10) % 10) + '0';
    rpm_arr[3] = (rpm % 10) + '0';

    can_transmit(RPM_MSG_ID, rpm_arr, 4);

    __delay_ms(80);

    //    can_receive(&rpm_msg_id, rpm_rec, &rpm_len);

    //    if (rpm_len >= 4) {
    ssd[0] = digit[rpm_rec[0] - '0'];
    ssd[1] = digit[rpm_rec[1] - '0'];
    ssd[2] = digit[rpm_rec[2] - '0'];
    ssd[3] = digit[rpm_rec[3] - '0'];

    display(ssd);

    return rpm;
}

uint16_t get_engine_temp() {
    //Implement the engine temperature function
}

IndicatorStatus process_indicator() {
    //Implement the indicator function
    key = read_digital_keypad(STATE_CHANGE);

    if (key == SWITCH1) {
        status = e_ind_left;
    } else if (key == SWITCH2) {
        status = e_ind_off;
    } else if (key == SWITCH3) {
        status = e_ind_right;
    }

    if (status == e_ind_left) {
        PORTBbits.RB0 = 1;
        PORTBbits.RB1 = 1;
        PORTBbits.RB6 = 0;
        PORTBbits.RB7 = 0;
    } else if (status == e_ind_off) {
        PORTBbits.RB0 = 0;
        PORTBbits.RB1 = 0;
        PORTBbits.RB6 = 0;
        PORTBbits.RB7 = 0;
    } else if (status == e_ind_right) {
        PORTBbits.RB0 = 0;
        PORTBbits.RB1 = 0;
        PORTBbits.RB6 = 1;
        PORTBbits.RB7 = 1;
    }

    ind_tx[0] = (unsigned char) status;

    can_transmit(INDICATOR_MSG_ID, ind_tx, 1);
    __delay_ms(80);

    //    can_receive(&ind_msg_id, ind_rx, &ind_len);

    //    status_rx = (IndicatorStatus) ind_rx[0];
    //
    //    if (status_rx == e_ind_left) {
    //        if (count_r++ < 5) {
    //            PORTBbits.RB0 = 1;
    //            PORTBbits.RB1 = 1;
    //            PORTBbits.RB6 = 0;
    //            PORTBbits.RB7 = 0;
    //        } 
    //        else {
    //            count_r = 0;
    //            PORTBbits.RB0 = 0;
    //            PORTBbits.RB1 = 0;
    //        }
    //
    //    } else if (status_rx == e_ind_off) {
    //        PORTBbits.RB0 = 0;
    //        PORTBbits.RB1 = 0;
    //        PORTBbits.RB6 = 0;
    //        PORTBbits.RB7 = 0;
    //    } else if (status_rx == e_ind_right) {
    //        if (count_l++ < 5) {
    //            PORTBbits.RB0 = 0;
    //            PORTBbits.RB1 = 0;
    //            PORTBbits.RB6 = 1;
    //            PORTBbits.RB7 = 1;
    //        } 
    //        else {
    //            count_l = 0;
    //            PORTBbits.RB6 = 0;
    //            PORTBbits.RB7 = 0;
    //        }
    //    }

    //        if (key == SWITCH1) {
    //            PORTBbits.RB0 = 1;
    //            PORTBbits.RB1 = 1;
    //            PORTBbits.RB6 = 0;
    //            PORTBbits.RB7 = 0;
    //        } else if (key == SWITCH2) {
    //            PORTBbits.RB0 = 0;
    //            PORTBbits.RB1 = 0;
    //            PORTBbits.RB6 = 0;
    //            PORTBbits.RB7 = 0;
    //        } else if (key == SWITCH3) {
    //            PORTBbits.RB0 = 0;
    //            PORTBbits.RB1 = 0;
    //            PORTBbits.RB6 = 1;
    //            PORTBbits.RB7 = 1;
    //        }
    return status;
}