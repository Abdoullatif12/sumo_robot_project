#include "assert_handler.h"
#include <proc/pic16f877a.h>
#include <builtins.h>

#define _XTAL_FREQ 16000000

/*
    Minimize code dependency in this function to prevent a accident call of function
    that could trigger assaert_handler (recursive call).
*/
void assert_handler(void)
{
    // TODO: Turn off the motors (safe state)
    // TODO: Trace to console
    // TODO: Breakpoint

    // Configure TEST_LED from registers
    TRISBbits.TRISB1 = 0b0;

    while (1) {
        /* code */
        PORTBbits.RB1 ^= 0b1;
        __delay_ms(200);
    }
}