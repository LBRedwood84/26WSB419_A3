#pragma once

#include "common.hpp"

#define MAX_PACKET 16 // 16 Bytes, allows for a few floats or a short string

// Internal use only, do not send structs over a network as that will include padding
typedef struct packet_t
{
    byte data[ MAX_PACKET ]; 
} packet_t;

// Interrupts are going to have to be disabled when reading anything greater than 8 bits
// Cant allow the value to change while reading it

typedef struct netaddr_t
{
    uint32_t ip;
    uint16_t port;

    // More C++ magic
    bool operator==( const netaddr_t& other ) { return (ip == other.ip) && (port == other.port); }
    bool operator!=( const netaddr_t& other) { return !(*this == other); }
    // Allows syntax like
    /*
     *  netaddr_t a, b;
     *  ....
     *  if (a == b)
     *    ....
     *
     */
} netaddr_t;

// Net channel, handles sequencing 
typedef struct netchan_t
{
    netaddr_t remote;
} netchan_t;


