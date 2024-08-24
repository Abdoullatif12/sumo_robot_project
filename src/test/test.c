#include "../common/defines.h"
#include "../drivers/io.h"
#include <stdio.h>
#include <builtins.h>

#define _XTAL_FREQ 16000000

/* 
 * Test the pin as gpio output and blink an LED */
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

/* static void test_blink_led()
{
    led_init();
    led_state_e state = LED_STATE_OFF;

    while (1) {
        state = (state == LED_STATE_OFF) ? LED_STATE_ON : LED_STATE_OFF;
        led_set(TEST_LED, state);
        __delay_ms(500);
    }
} */

/* Test a pin as gpio input by turning an LED on, when logic HIGH is applied on the pin */
static void test_inputs()
{
    const io_config led_config = { .select = IO_SELECT_GPIO,
                                   .dir = IO_DIR_OUTPUT,
                                   .resistor = IO_RESISTOR_DISABLED,
                                   .out = IO_OUT_LOW };

    const io_config input_config = { .select = IO_SELECT_GPIO,
                                     .dir = IO_DIR_INPUT,
                                     .resistor = IO_RESISTOR_DISABLED,
                                     .out = IO_OUT_LOW };

    io_configure(IO_TEST_LED, &led_config);

    io_configure(UNUSED_15, &input_config);

    while (1) {

        io_in_e inputState = io_get_gpio_input(UNUSED_15);

        io_out_e out = (inputState == IO_IN_HIGH) ? IO_OUT_HIGH : IO_OUT_LOW;
        io_set_out(IO_TEST_LED, out);
    }
}

/*
 * Configure all pins as output and toggle them in a loop.
 * Then verify with a logic analyzer. */

static void test_io_pins_output(void)
{

    const io_config output_config = { .select = IO_SELECT_GPIO,
                                      .dir = IO_DIR_OUTPUT,
                                      .resistor = IO_RESISTOR_DISABLED,
                                      .out = IO_OUT_LOW };

    for (io_generic_e io = IO_00; io <= IO_42; io++) {
        io_configure(io, &output_config);
    }

    while (1) {
        for (io_generic_e io = IO_00; io <= IO_42; io++) {
            io_set_out(io, IO_OUT_HIGH);
            __delay_ms(1000);
            io_set_out(io, IO_OUT_LOW);
        }
    }
}


/*
 * Configure all pins (except LED pin) as input and apply logic HIGH to them to
 * turn on an LED */

static void test_io_pins_input(void)
{   
    // led configuration struct
    const io_config led_config = { .select = IO_SELECT_GPIO,
                                   .dir = IO_DIR_OUTPUT,
                                   .resistor = IO_RESISTOR_DISABLED,
                                   .out = IO_OUT_LOW };

    // gpio configuration struct
    const io_config input_config = { .select = IO_SELECT_GPIO,
                                     .dir = IO_DIR_INPUT,
                                     .resistor = IO_RESISTOR_DISABLED,
                                     .out = IO_OUT_LOW };

    
    // configure pins as input except led pin
    for (io_generic_e io = IO_00; io <= IO_42; io++) {
        io_configure(io, &input_config);
    }

    io_configure(IO_TEST_LED, &led_config);

    for (io_generic_e io = IO_00; io <= IO_42; io++) {

        if(io == IO_TEST_LED){
            continue;
        }

        io_set_out(IO_TEST_LED, IO_OUT_LOW);

        // wait until the pin is pulled high
        while (io_get_gpio_input(io) == IO_IN_LOW)
        {
            __delay_ms(100);
        }

        // when the pin is pulled high, we turn on the led
        io_set_out(IO_TEST_LED, IO_OUT_HIGH);
        
        // wait until the pin is pulled low
        while (io_get_gpio_input(io) == IO_IN_HIGH)
        {
            __delay_ms(100);
        }
    }

    // Blink led when test is done
    while (1)
    {
        io_set_out(IO_TEST_LED, IO_OUT_HIGH);
        __delay_ms(1000);
        io_set_out(IO_TEST_LED, IO_OUT_LOW);
        __delay_ms(1000);
    }
    
}

static void test_assert()
{
    ASSERT(0);
}


