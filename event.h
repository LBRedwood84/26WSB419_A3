#ifndef EVENT_H
#define EVENT_H

typedef enum event_type_t : unsigned char
{
    EVENT_STEER = 0,
    EVENT_FORWARD, // Set both wheels to the same value
    EVENT_BACKWARDS, // Set both wheels to the same value, negative
    EVENT_COUNT, // Not an event, it is the number of enums above
} event_type_t;



typedef struct event_t
{
    event_type_t type;
    // A union allows all of the following fields to exist in the same memory
    // Takes us down from occupying 3 floats of memory to one
    union
    {
        float steer; // -1 to 1 value from analogue trigger
        float foward; // 0 to 1 value from right trigger
        float backward; // 0 to 1 value from left trigger
    };
} event_t;

#define MAX_EVENTS 16
typedef struct boebot_t boebot_t;

typedef struct event_queue_t
{
    event_t events[MAX_EVENTS];
    unsigned char head, tail;

    // Avoid branching by storing an array of function pointers
    // Each function stored at the index of the corresponding event
    void (*event_handlers[EVENT_COUNT])( boebot_t* bot, event_t* event );

} event_queue_t;

extern event_t* gCurrentEvent;
extern event_queue_t gEventQueue;

void EventQueue_Init( void );
void EventQueue_Push( event_t event );
void EventQueue_Process( boebot_t* bot );


#endif
