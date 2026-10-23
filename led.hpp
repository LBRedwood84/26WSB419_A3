#pragma once

#include "common.hpp"
#include <Arduino.h>

typedef struct led_t
{
    int pin;
    unsigned char brightness; // 0 - 255
    unsigned long last_toggle; // For non-blocking blink behaviour
    unsigned long blink_delay;
    bool active;
} led_t;



// Initialisation
void LED_SetPin( led_t* led, int pin );

static void LED_SetBrightnessFraction( led_t* led, float fraction ) // Set the brightness as a fraction of its maximum
{
    float frac = fraction;
    clamp(0.0f, 1.0f, &frac);
    led->brightness = 255 * frac;
}


static void LED_SetBrightnessValue( led_t* led, unsigned char brightness )
{
    led->brightness = brightness;
}


void LED_SetBlinkDelay( led_t* led, unsigned long delay_ms ); // Set the blinking interval in ms


// Blink the LED if the time is appropriate
void LED_Blink( led_t* led, unsigned long current_time, unsigned long delay_ms ); 

// Writes the brightness to the pin
void LED_WriteOn( led_t* led );
// Writes 0 to the pin
void LED_WriteOff( led_t* led );

// Write (fraction * brightness) to the pin
void LED_WriteAnalog( led_t* led, float fraction ); 
// Write the directy brightness value to the pin
void LED_WriteAnalog( led_t* led, unsigned char brightness );


