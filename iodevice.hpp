#pragma once
#include "common.hpp"

#include <stdint.h>
enum class PinType : uint8_t
{
    Input = 0, Output = 1
};

class IODevice
{
public:
    virtual ~IODevice( void ) = default;
    virtual void SetPin( pin_t pin, PinType type ); 
    
    
    virtual void DigitalWrite( uint8_t value );
    virtual int DigitalRead( void );

    virtual void AnalogWrite( int value );
    virtual int AnalogRead( void );


    pin_t GetPin( void ) const { return m_pin; }        
protected:
    pin_t m_pin;
};




class LED : public IODevice
{
public:
    
    LED( pin_t pin ) { SetPin( pin, PinType::Output); }
    void SetBrightness( uint8_t brightness );
    uint8_t GetBrightness( void ) const { return m_brightnessvalue; }
    void SetBrightnessFraction( float fraction );
    void SetBlinkDelay( unsigned long delay_ms ) { m_blink_delay = delay_ms; }
    
    void Blink( void );

private:
    uint8_t m_brightnessvalue = 255;
    unsigned long m_blink_delay = 1000;
    unsigned long m_last_blink = 0;
};




// forward declaration
class NIC;

class Boebot
{
public:
    Boebot( void ) = default;
    ~Boebot( void ) = default;

    inline void ResetState( void ) { memset(&m_drivestate, 0, sizeof(m_drivestate)); }
    
    inline void AttachNIC( NIC* nic );

private:
    struct 
    {
        // Obtained
        float steer;
        float forward, backward;
        // Derived
        float L, R;
    } m_drivestate;
    
    NIC* m_nic = nullptr;

};
