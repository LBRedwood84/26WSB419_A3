#pragma once

#include "net.hpp"
#include "iodevice.hpp"

// This is an input device to the Arduino
class NIC : public IODevice
{
public:
    NIC( pin_t pin ) {SetPin( pin, PinType::Input); }


private:

};
