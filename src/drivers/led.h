#ifndef LED_H
#define LED_H

// Simple driver for controlling LED connected to a gpio

typedef enum
{
    TEST_LED,
} led_e;

typedef enum
{
    LED_STATE_OFF,
    LED_STATE_ON,
} led_state_e;

void led_init(void);
void led_set(led_e led, led_state_e state);

#endif