#pragma once

#include <Arduino.h>
#define MAX_MSG 64 // Tight limit

typedef unsigned char pin_t; // 8 bits
                             //
                             //


extern unsigned long current_time;

#ifdef __cplusplus
template <typename T>
inline void clamp( T min, T max, T *value )
{
  T val = *value;
  val = MAX( val, min );
  val = MIN( val, max );
  *value = val;
}
  
template <typename T>
inline T MAX( T a, T b )
{
    return (a > b) ? a : b;
}

template <typename T>
inline T MIN( T a, T b )
{
    return (a < b) ? a : b;
}

template <typename T>
inline T MAX3( T a, T b, T c )
{
    return (MAX(a, b), c);
}

template <typename T>
inline T MIN3( T a, T b, T c )
{
    return (MIN(a, b), c);
}
#endif


/*
typedef struct pin_t
{
    int handle; // Pin number, e.g 13
    char io; // Is this an input or output pin
} pin_t;
*/

/*
 
Arduino UNO bus width is one byte, avoid using the longer types to minimise cycles

It has 32KB of flash memory and only 2KB of dynamic memory.

The arduino header defined the F() macro

#define F(string_literal) (reinterpret_cast<const __FlashStringHelper *>(PSTR(string_literal)))

Which moves a string literal into flash memory.

e.g Serial.print( F("Hello, world!") );

*/



/**
 * @brief Maps a floating-point value from one range to another.
 * 
 * @param x        The input value to map.
 * @param in_min   The lower bound of the input range.
 * @param in_max   The upper bound of the input range.
 * @param out_min  The lower bound of the output range.
 * @param out_max  The upper bound of the output range.
 * @return float   The mapped value.
 */
static inline float map_float(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#include <stdarg.h>
#include <stdio.h>

static inline void SerialMessage( const char *fmt, ... )
{
    char buf[MAX_MSG];
    va_list args;
    va_start(args, fmt );
    vsnprintf(buf, MAX_MSG, fmt, args );
    va_end(args);
    buf[ MAX_MSG - 1 ] = 0; // null terminate
    Serial.print(buf);
}

static inline unsigned long CurrentTime( void )
{
    return millis();
}


// Some reason C++ doesnt provide an inline rounding function?
static inline int rnd_float_int( float value )
{
    return (int)(value + 0.5f);
}


static inline float rnd_float(float var)
{
    // 37.66666 * 100 =3766.66
    // 3766.66 + .5 =3767.16    for rounding off value
    // then type cast to int so value is 3767
    // then divided by 100 so the value converted into 37.67
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}

