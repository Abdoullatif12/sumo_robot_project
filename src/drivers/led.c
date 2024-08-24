#include "led.h"
#include "io.h"
#include <stdbool.h>
#include "../common/assert_handler.h"

/*
 The LED io pin should be configured in io_init() function in mcu_init().
 An assert will be used to ensure it actually is.
*/

const io_config led_config = { .select = IO_SELECT_GPIO,
                               .dir = IO_DIR_OUTPUT,
                               .resistor = IO_RESISTOR_DISABLED,
                               .out = IO_OUT_LOW };

static bool initialized = false;
void led_init(void)
{
    ASSERT(!initialized);
    io_config current_config;
    io_get_current_config(IO_TEST_LED, &current_config);
    ASSERT(io_compare_config(current_config, led_config));
    initialized = true;
}

void led_set(led_e led, led_state_e state)
{
    ASSERT(initialized);
    io_out_e out = (state == LED_STATE_ON) ? IO_OUT_HIGH : IO_OUT_LOW;
    switch (led) {
    case TEST_LED:
        io_set_out(IO_TEST_LED, out);
        break;
    }

    // TODO: Assert initialized
}
