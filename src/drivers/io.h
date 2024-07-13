#ifndef IO_H
#define IO_H

#include <stdbool.h>
#include <stdint.h>

/* IO pins handling including pinmapping, initialization and configuration
 * This wraps the crude register defines
 */

/* IO numbering
  the IOs are labeled so that the tens digit represents the port and the units
  digit represents the pin
*/
typedef enum
{
    IO_00,
    IO_01,
    IO_02,
    IO_03,
    IO_04,
    IO_05,
    IO_06,
    IO_07,
    IO_10,
    IO_11,
    IO_12,
    IO_13,
    IO_14,
    IO_15,
    IO_16,
    IO_17,
    IO_20,
    IO_21,
    IO_22,
    IO_23,
    IO_24,
    IO_25,
    IO_26,
    IO_27,
    IO_30,
    IO_31,
    IO_32,
    IO_33,
    IO_34,
    IO_35,
    IO_36,
    IO_37,
    IO_40,
    IO_41,
    IO_42,
} generic_io_e;

// Pin definition
typedef enum
{
    IO_LINE_DETECT_FRONT_LEFT = IO_00,
    IO_LINE_DETECT_FRONT_RIGHT = IO_01,
    IO_LINE_DETECT_BACK_LEFT = IO_02,
    IO_LINE_DETECT_BACK_RIGHT = IO_03,
    IO_UART_RXD = IO_26,
    IO_UART_TXD = IO_27,
    IO_I2C_SCL = IO_23,
    IO_I2C_SDA = IO_24,
    IO_IR_REMOTE = IO_11,
    IO_RANGESENSOR_FRONT_INT = IO_10,
    IO_XSHUT_FRONT_LEFT = IO_13,
    IO_XSHUT_FRONT = IO_34,
    IO_XSHUT_FRONT_RIGHT = IO_35,
    IO_XSHUT_LEFT = IO_36,
    IO_XSHUT_RIGHT = IO_37,
    IO_MOTOR_LEFT_CC_1 = IO_30,
    IO_MOTOR_LEFT_CC_2 = IO_31,
    IO_MOTOR_RIGHT_CC_1 = IO_32,
    IO_MOTOR_RIGHT_CC_2 = IO_33,
    IO_TEST_LED = IO_11,
    PWM_MOTORS_LEFT = IO_21,
    PWM_MOTORS_RIGHT = IO_21, // Same pwm signal with the other mother (tank drive principle)
    UNUSED_1 = IO_04,
    UNUSED_2 = IO_05,
    UNUSED_3 = IO_14,
    UNUSED_4 = IO_15,
    UNUSED_5 = IO_16,
    UNUSED_6 = IO_17,
    UNUSED_7 = IO_20,
    UNUSED_8 = IO_22,
    UNUSED_9 = IO_25,
    UNUSED_10 = IO_40,
    UNUSED_11 = IO_41,
    UNUSED_12 = IO_42
} io_e;

// Pin Configuration
typedef enum
{
    IO_SELECT_GPIO,
    IO_SELECT_ALT
} io_select_e;

// Pin direction settings
typedef enum
{
    IO_DIR_OUTPUT,
    IO_DIR_INPUT
} io_dir_e;

// Pin level
typedef enum
{
    IO_IN_LOW,
    IO_IN_HIGH
} io_in_e;

typedef enum
{
    IO_OUT_LOW,
    IO_OUT_HIGH
} io_out_e;

typedef enum
{
    IO_RESISTOR_ENABLED,
    IO_RESISTOR_DISABLED
} io_resistor_e;

// TODO: structs
typedef struct io_config
{
    io_select_e select;
    io_dir_e dir;
    io_resistor_e resistor;
    io_out_e out;
} io_config;

// TODO: functions
void io_set_select(io_e io, io_select_e select);
void io_set_direction(io_e io, io_dir_e direction);
io_in_e io_get_input(io_e io);
void io_set_resistor(io_e io, io_resistor_e resistor);
void io_set_out(io_e io, io_out_e out);
void io_configure(io_e io, const io_config *config);

#endif