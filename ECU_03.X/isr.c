 /*
 * File:   isr.c
 * Author: OMKAR SAWANT
 *
 * Created on 8 April, 2026, 9:44 AM
 */


#include <xc.h>
#include "isr.h"

volatile unsigned int count = 0;
volatile unsigned char blink_flag = 0;

void __interrupt() isr() {
    if (INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        TMR0 = TMR0 + 8;
        count++;

        if (count >= 20000) {
            count = 0;
            blink_flag = !blink_flag;
        }
    }
}