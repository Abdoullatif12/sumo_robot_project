#include "common/defines.h"
#include "drivers/mcu_init.h"
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

int main()
{
    mcu_init();
    return 0;
}