#ifndef IO_H
#define IO_H

/* IO pins handling including pinmapping, initialization and configuration
 * This wraps the crude register defines
 */

// Pin definition
typedef enum {
  IO_LINE_DETECT_FRONT_RIGHT,
  IO_LINE_DETECT_FRONT_LEFT,
  IO_LINE_DETECT_BACK_LEFT,
  IO_LINE_DETECT_BACK_RIGHT,
  IO_UART_RXD,
  IO_UART_TXD,
  IO_I2C_SCL,
  IO_I2C_SDA,
  IO_IR_REMOTE,
  IO_RANGESENSOR_FRONT_INT,
  IO_XSHUT_FRONT,
  IO_XSHUT_RIGHT,
  IO_XSHUT_LEFT,
  IO_XSHUT_FRONT_RIGHT,
  IO_XSHUT_FRONT_LEFT,
  IO_MOTOR_LEFT_CC_2,
  IO_MOTOR_LEFT_CC_1,
  IO_MOTOR_RIGHT_CC_2,
  IO_MOTOR_RIGHT_CC_1,
  IO_TEST_LED,
  PWM_MOTORS_LEFT,
  PWM_MOTORS_RIGHT,
  UNUSED_1,
  UNUSED_2,
  UNUSED_3,
  UNUSED_4,
  UNUSED_5,
  UNUSED_6,
  UNUSED_7,
  UNUSED_8,
  UNUSED_9,
} io_e;

// Pin Configuration
typedef enum { IO_SELECT_GPIO, IO_SELECT_ALT } io_select_e;

// Pin direction settings
typedef enum { IO_DIR_INPUT, IO_DIR_OUTPUT } io_dir_e;

// Pin level
typedef enum { IO_IN_LOW, IO_IN_HIGH } io_in_e;

// TODO: structs
// TODO: functions
void io_set_select(io_e io, io_select_e select);
void io_set_direction(io_e io, io_dir_e direction);
io_in_e io_get_input(io_e io);

#endif