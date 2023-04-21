// Autogenerated with StateSmith 0.9.2-alpha.
// Algorithm: Balanced1. See https://github.com/StateSmith/StateSmith/wiki/Algorithms

#pragma once
#include <stdint.h>

// any text you put in IRenderConfigC.HFileIncludes (like this comment) will be written to the generated .h file
typedef enum Blinky1Sm_EventId
{
    Blinky1Sm_EventId_DO = 0, // The `do` event is special. State event handlers do not consume this event (ancestors all get it too) unless a transition occurs.
} Blinky1Sm_EventId;

enum
{
    Blinky1Sm_EventIdCount = 1
};

typedef enum Blinky1Sm_StateId
{
    Blinky1Sm_StateId_ROOT = 0,
    Blinky1Sm_StateId_LED_OFF = 1,
    Blinky1Sm_StateId_LED_ON = 2,
} Blinky1Sm_StateId;

enum
{
    Blinky1Sm_StateIdCount = 3
};


// Generated state machine
// forward declaration
typedef struct Blinky1Sm Blinky1Sm;

// State machine variables. Can be used for inputs, outputs, user variables...
typedef struct Blinky1Sm_Vars
{
    uint32_t timer_started_at_ms;  // milliseconds
} Blinky1Sm_Vars;


// event handler type
typedef void (*Blinky1Sm_Func)(Blinky1Sm* sm);

// State machine constructor. Must be called before start or dispatch event functions. Not thread safe.
void Blinky1Sm_ctor(Blinky1Sm* sm);

// Starts the state machine. Must be called before dispatching events. Not thread safe.
void Blinky1Sm_start(Blinky1Sm* sm);

// Dispatches an event to the state machine. Not thread safe.
void Blinky1Sm_dispatch_event(Blinky1Sm* sm, Blinky1Sm_EventId event_id);

// Thread safe.
char const * Blinky1Sm_state_id_to_string(Blinky1Sm_StateId id);

// Thread safe.
char const * Blinky1Sm_event_id_to_string(Blinky1Sm_EventId id);

// Generated state machine
struct Blinky1Sm
{
    // Used internally by state machine. Feel free to inspect, but don't modify.
    Blinky1Sm_StateId state_id;
    
    // Used internally by state machine. Don't modify.
    Blinky1Sm_Func ancestor_event_handler;
    
    // Used internally by state machine. Don't modify.
    Blinky1Sm_Func current_event_handlers[Blinky1Sm_EventIdCount];
    
    // Used internally by state machine. Don't modify.
    Blinky1Sm_Func current_state_exit_handler;
    
    // Variables. Can be used for inputs, outputs, user variables...
    Blinky1Sm_Vars vars;
};

