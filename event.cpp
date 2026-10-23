#include "event.h"
#include "boebot.hpp"
#include "common.hpp"

event_t* gCurrentEvent = nullptr;
extern event_queue_t gEventQueue = {};
typedef unsigned char qindex_t;

void steer_event( boebot_t* bot, event_t* e )
{
    bot->steer = e->steer;
}

void forward_event( boebot_t* bot, event_t* e )
{
    bot->forward = e->foward;
}
void backward_event( boebot_t* bot, event_t* e )
{
    bot->back = e->backward;
}


void EventQueue_Init( void )
{
    gEventQueue.event_handlers[EVENT_STEER] = steer_event;
    gEventQueue.event_handlers[EVENT_BACKWARDS] = backward_event;
    gEventQueue.event_handlers[EVENT_FORWARD] = forward_event;
}

void EventQueue_Push( event_t event )
{
    qindex_t next = ( gEventQueue.tail + 1 ) % MAX_EVENTS;
    if (next == gEventQueue.head){
        // Queue is full, how to handle this event?
        return; // Skip for now
    }
    gEventQueue.events[gEventQueue.tail] = event;
    gEventQueue.tail = next;
}

void EventQueue_Process( boebot_t* bot )
{
    while (gEventQueue.head != gEventQueue.tail)
    {
        event_t* e = &gEventQueue.events[gEventQueue.head];
        if (gEventQueue.event_handlers[e->type] == NULL)
        {
            SerialMessage("EventQueue: Event received, but has no handler function!\n");
            continue;
        }
        gEventQueue.event_handlers[e->type](bot, e);
        gEventQueue.head = (gEventQueue.head + 1 ) % MAX_EVENTS;
    }
}



