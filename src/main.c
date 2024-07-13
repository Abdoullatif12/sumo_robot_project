#include "common/defines.h"
#include "drivers/io.h"
#include <stdio.h>
#include <builtins.h>

// CONFIG
#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit
                        // (RB3/PGM pin has PGM function; low-volt>#pragma config CPD = OFF // Data
                        // EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write Enable bits (Write protection off; all
                         // program memory may be written to by EECON >#pragma config CP = OFF //
                         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 16000000

/*
    TODO: Move to test file
    static void test_blink_led()
{
    const io_config led_config = { .select = IO_SELECT_GPIO,
                                   .dir = IO_DIR_OUTPUT,
                                   .resistor = IO_RESISTOR_DISABLED,
                                   .out = IO_OUT_LOW };

    io_configure(IO_TEST_LED, &led_config);
    io_out_e out = IO_OUT_LOW;

    while (1) {
        out = (out == IO_OUT_LOW) ? IO_OUT_HIGH : IO_OUT_LOW;
        io_set_out(IO_TEST_LED, out);
        __delay_ms(1000);
    }
}
*/

int main()
{
    return 0;
}