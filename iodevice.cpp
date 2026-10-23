#include "iodevice.hpp"
#include "common.hpp"

#include "Arduino.h"

void IODevice::SetPin( pin_t pin, PinType type )
{
    m_pin = pin;
    pinMode( m_pin, static_cast<uint8_t>(type) );
}

void IODevice::DigitalWrite( uint8_t value )
{
    digitalWrite( m_pin, value );
}

int IODevice::DigitalRead()
{
    return digitalRead( m_pin );
}

void IODevice::AnalogWrite( int value )
{
    analogWrite( m_pin, value );
}

int IODevice::AnalogRead( void )
{
    return analogRead( m_pin );
}


void LED::SetBrightness( uint8_t brightness )
{
    m_brightnessvalue = brightness;
    clamp( (uint8_t)0, (uint8_t)255, &m_brightnessvalue );
}

void LED::SetBrightnessFraction( float fraction )
{
    float frac = fraction;
    clamp( 0.0f, 1.0f, &frac );
    m_brightnessvalue = 255 * frac;
}


void LED::Blink( void )
{
   if (current_time - m_last_blink > m_blink_delay)
   {
       AnalogWrite( m_brightnessvalue );
       m_last_blink = current_time;
   }
}



