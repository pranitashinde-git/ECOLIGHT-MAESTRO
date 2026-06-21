#include <LPC21xx.h>

#define LED (1<<10)

void led_init(void)
{
    // Make P0.10 as OUTPUT

    IODIR0 |= LED;
}

void led_on(void)
{
    // LED ON

    IOSET0 = LED;
}

void led_off(void)
{
    // LED OFF

    IOCLR0 = LED;
}