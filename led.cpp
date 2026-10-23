#include "led.hpp"

#include "common.hpp"



void LED_SetBlinkDelay( led_t* led, unsigned long delay_ms )
{
    if (!led) return;
    led->blink_delay = delay_ms;
}


void LED_WriteOn( led_t* led )
{
    analogWrite( led->pin, led->brightness );
}

void LED_WriteAnalog( led_t* led, float fraction )
{
    if (!led) return;
    float frac = fraction;
    clamp(0.0f, 1.0f, &frac);

    analogWrite( led->pin, rnd_float_int(255.0f * frac) );
}

void LED_WriteAnalog( led_t* led, unsigned char brightness )
{
    if (!led) return;
    analogWrite( led->pin, brightness );
}





void LED_WriteOff( led_t* led )
{
    analogWrite( led->pin, 0 );
}


void LED_SetPin( led_t* led, int pin )
{
    if (!led) return;
    pinMode( pin, OUTPUT );
    led->pin = pin;
}

void LED_Blink( led_t* led, unsigned long current_time, unsigned long delay_ms )
{
    if (current_time - led->last_toggle < delay_ms)
        return;

    led->last_toggle = current_time;
    led->active = !led->active;
    LED_WriteOn( led );
}
