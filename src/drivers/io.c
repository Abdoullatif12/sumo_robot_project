#include "io.h"
#include "../common/defines.h"
//#include <xc.h>
#include <proc/pic16f877a.h>

#define IO_PORT_CNT (5u)
#define IO_PIN_CNT_PER_PORT (8u)
#define IO_PIN_CNT (IO_PORT_CNT * IO_PIN_CNT_PER_PORT - 5)

/* Unused pins will be configured as output and set to low
 * since input pins do not have pull-up or pull-down resistors*/
#define UNUSED_CONFIG                                                                              \
    {                                                                                              \
        IO_SELECT_GPIO, IO_DIR_OUTPUT, IO_RESISTOR_DISABLED, IO_OUT_LOW                            \
    }

/* This array holds the initial configuration for all IO pins
 */
static const io_config io_initial_configs[IO_PIN_CNT] = {
    // test led output
    [IO_TEST_LED] = { IO_SELECT_GPIO, IO_DIR_OUTPUT, IO_RESISTOR_DISABLED, IO_OUT_LOW },

    // unused pins
    [IO_LINE_DETECT_FRONT_LEFT] = UNUSED_CONFIG,
    [IO_LINE_DETECT_FRONT_RIGHT] = UNUSED_CONFIG,
    [IO_LINE_DETECT_BACK_LEFT] = UNUSED_CONFIG,
    [IO_LINE_DETECT_BACK_RIGHT] = UNUSED_CONFIG,
    [IO_UART_RXD] = UNUSED_CONFIG,
    [IO_UART_TXD] = UNUSED_CONFIG,
    [IO_I2C_SCL] = UNUSED_CONFIG,
    [IO_I2C_SDA] = UNUSED_CONFIG,
    [IO_IR_REMOTE] = UNUSED_CONFIG,
    [IO_RANGESENSOR_FRONT_INT] = UNUSED_CONFIG,
    [IO_XSHUT_FRONT_LEFT] = UNUSED_CONFIG,
    [IO_XSHUT_FRONT] = UNUSED_CONFIG,
    [IO_XSHUT_FRONT_RIGHT] = UNUSED_CONFIG,
    [IO_XSHUT_LEFT] = UNUSED_CONFIG,
    [IO_XSHUT_RIGHT] = UNUSED_CONFIG,
    [IO_MOTOR_LEFT_CC_1] = UNUSED_CONFIG,
    [IO_MOTOR_LEFT_CC_2] = UNUSED_CONFIG,
    [IO_MOTOR_RIGHT_CC_1] = UNUSED_CONFIG,
    [IO_MOTOR_RIGHT_CC_2] = UNUSED_CONFIG,
    [PWM_MOTORS_LEFT] = UNUSED_CONFIG,
    [PWM_MOTORS_RIGHT] = UNUSED_CONFIG,
    [UNUSED_04] = UNUSED_CONFIG,
    [UNUSED_05] = UNUSED_CONFIG,
    [UNUSED_14] = UNUSED_CONFIG,
    [UNUSED_15] = UNUSED_CONFIG,
    [UNUSED_16] = UNUSED_CONFIG,
    [UNUSED_17] = UNUSED_CONFIG,
    [UNUSED_20] = UNUSED_CONFIG,
    [UNUSED_22] = UNUSED_CONFIG,
    [UNUSED_25] = UNUSED_CONFIG,
    [UNUSED_40] = UNUSED_CONFIG,
    [UNUSED_41] = UNUSED_CONFIG,
    [UNUSED_42] = UNUSED_CONFIG,
};

/*
 * IOs are structured in such a way we can get the corresponding port
 * and pin from the IO enum.
 *  - The three least bit represent the pin number
 *  - The following three bit represent the port number
 * [Zeros (2 bits) | Ports (3 bits) | Pins (3 bits)]
 *
 * We can extract the port and pin number by shifting and masking.
 */
#define IO_PORT_OFFSET (3u)
#define IO_PORT_MASK (0x7u << IO_PORT_OFFSET)
#define IO_PIN_MASK (0x7u)

static inline uint8_t io_port(io_e io)
{
    return (io & IO_PORT_MASK) >> IO_PORT_OFFSET;
}

// The pin index represent the pin number in decimal
static inline uint8_t io_pin_idx(io_e io)
{
    return (io & IO_PIN_MASK);
}

// The pin bit is the bit that represent the pin position in the register
static inline uint8_t io_pin_bit(io_e io)
{
    return 1 << io_pin_idx(io);
}

static volatile unsigned char *port_dir_regs[IO_PORT_CNT] = { &TRISA, &TRISB, &TRISC, &TRISD,
                                                              &TRISE };
static volatile unsigned char *port_in_out_regs[IO_PORT_CNT] = { &PORTA, &PORTB, &PORTC, &PORTD,
                                                                 &PORTE };

/*
 * By default the PIC16f877a does not have registers to configure pins as gpio.
 * Therefore when a pin is selected as gpio, the fonction will just configure it
 * as digital input.
 */
/* // cppcheck-suppress unusedFunction */
void io_set_select(io_e io, io_select_e select)
{
    uint8_t port = io_port(io);
    uint8_t pin = io_pin_bit(io);

    switch (select) {
    case IO_SELECT_GPIO:
        *port_dir_regs[port] |= pin;

        // Special case for pins that support analog inputs
        if (port == 0 || port == 4) {
            ADCON1 = 0x6;
        }
        break;
    default:
        break;
    }
}

/* // cppcheck-suppress unusedFunction */
void io_set_direction(io_e io, io_dir_e direction)
{
    uint8_t port = io_port(io);
    uint8_t pin = io_pin_bit(io);

    switch (direction) {
    case IO_DIR_INPUT:
        *port_dir_regs[port] |= pin;
        break;
    case IO_DIR_OUTPUT:
        *port_dir_regs[port] &= ~pin;
        break;
    }
}

// Enabling pullup resistors on PORTB
/* // cppcheck-suppress unusedFunction */
void io_set_resistor(io_e io, io_resistor_e resistor)
{
    uint8_t port = io_port(io);
    if (port == 1) {
        switch (resistor) {
        case IO_RESISTOR_ENABLED:
            OPTION_REGbits.nRBPU = 0;
            break;
        case IO_RESISTOR_DISABLED:
            OPTION_REGbits.nRBPU = 1;
            break;
        }
    }
}

/* // cppcheck-suppress unusedFunction */
void io_set_out(io_e io, io_out_e out)
{
    uint8_t port = io_port(io);
    uint8_t pin = io_pin_bit(io);

    switch (out) {
    case IO_OUT_LOW:
        *port_in_out_regs[port] &= ~pin;
        break;

    case IO_OUT_HIGH:
        *port_in_out_regs[port] |= pin;
        break;
    }
}

/* // cppcheck-suppress unusedFunction */
io_in_e io_get_gpio_input(io_e io)
{
    uint8_t port = io_port(io);
    uint8_t pin = io_pin_bit(io);

    return (*port_in_out_regs[port] & pin) ? IO_IN_HIGH : IO_IN_LOW;
}

/* // cppcheck-suppress unusedFunction */
void io_configure(io_e io, const io_config *config)
{
    io_set_select(io, config->select);
    io_set_direction(io, config->dir);
    io_set_out(io, config->out);
    io_set_resistor(io, config->resistor);
}

void io_init(void)
{
    // loop and configure all pins using the configuration array
    for (io_e io = IO_00; io < ARRAY_SIZE(io_initial_configs); io++) {
        io_configure(io, &io_initial_configs[io]);
    }
}