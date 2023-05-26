// Autogenerated with StateSmith.
// Algorithm: Balanced1. See https://github.com/StateSmith/StateSmith/wiki/Algorithms

#include "Ex1.h"
#include <stdbool.h> // required for `consume_event` flag
#include <string.h> // for memset

// This function is used when StateSmith doesn't know what the active leaf state is at
// compile time due to sub states or when multiple states need to be exited.
static void exit_up_to_state_handler(Ex1* sm, Ex1_Func desired_state_exit_handler);

static void ROOT_enter(Ex1* sm);

static void ROOT_exit(Ex1* sm);

static void STATE_1_enter(Ex1* sm);

static void STATE_1_exit(Ex1* sm);

static void STATE_1_do(Ex1* sm);

static void STATE_2_enter(Ex1* sm);

static void STATE_2_exit(Ex1* sm);


// State machine constructor. Must be called before start or dispatch event functions. Not thread safe.
void Ex1_ctor(Ex1* sm)
{
    memset(sm, 0, sizeof(*sm));
}

// Starts the state machine. Must be called before dispatching events. Not thread safe.
void Ex1_start(Ex1* sm)
{
    ROOT_enter(sm);
    // ROOT behavior
    // uml: TransitionTo(ROOT.<InitialState>)
    {
        // Step 1: Exit states until we reach `ROOT` state (Least Common Ancestor for transition). Already at LCA, no exiting required.
        
        // Step 2: Transition action: ``.
        
        // Step 3: Enter/move towards transition target `ROOT.<InitialState>`.
        // ROOT.<InitialState> is a pseudo state and cannot have an `enter` trigger.
        
        // ROOT.<InitialState> behavior
        // uml: TransitionTo(STATE_1)
        {
            // Step 1: Exit states until we reach `ROOT` state (Least Common Ancestor for transition). Already at LCA, no exiting required.
            
            // Step 2: Transition action: ``.
            
            // Step 3: Enter/move towards transition target `STATE_1`.
            STATE_1_enter(sm);
            
            // Step 4: complete transition. Ends event dispatch. No other behaviors are checked.
            sm->state_id = Ex1_StateId_STATE_1;
            // No ancestor handles event. Can skip nulling `ancestor_event_handler`.
            return;
        } // end of behavior for ROOT.<InitialState>
    } // end of behavior for ROOT
}

// Dispatches an event to the state machine. Not thread safe.
void Ex1_dispatch_event(Ex1* sm, Ex1_EventId event_id)
{
    Ex1_Func behavior_func = sm->current_event_handlers[event_id];
    
    while (behavior_func != NULL)
    {
        sm->ancestor_event_handler = NULL;
        behavior_func(sm);
        behavior_func = sm->ancestor_event_handler;
    }
}

// This function is used when StateSmith doesn't know what the active leaf state is at
// compile time due to sub states or when multiple states need to be exited.
static void exit_up_to_state_handler(Ex1* sm, Ex1_Func desired_state_exit_handler)
{
    while (sm->current_state_exit_handler != desired_state_exit_handler)
    {
        sm->current_state_exit_handler(sm);
    }
}


////////////////////////////////////////////////////////////////////////////////
// event handlers for state ROOT
////////////////////////////////////////////////////////////////////////////////

static void ROOT_enter(Ex1* sm)
{
    // setup trigger/event handlers
    sm->current_state_exit_handler = ROOT_exit;
}

// The root exit function can't actually be called so we add code coverage hints.
// LCOV_EXCLUDE_START
// GCOV_EXCLUDE_START
// GCOVR_EXCLUDE_START
static void ROOT_exit(Ex1* sm)
{
    // State machine root is a special case. It cannot be exited. Mark as unused.
    (void)sm;
}
// LCOV_EXCLUDE_STOP
// GCOV_EXCLUDE_STOP
// GCOVR_EXCLUDE_STOP

////////////////////////////////////////////////////////////////////////////////
// event handlers for state STATE_1
////////////////////////////////////////////////////////////////////////////////

static void STATE_1_enter(Ex1* sm)
{
    // setup trigger/event handlers
    sm->current_state_exit_handler = STATE_1_exit;
    sm->current_event_handlers[Ex1_EventId_DO] = STATE_1_do;
}

static void STATE_1_exit(Ex1* sm)
{
    // adjust function pointers for this state's exit
    sm->current_state_exit_handler = ROOT_exit;
    sm->current_event_handlers[Ex1_EventId_DO] = NULL;  // no ancestor listens to this event
}

static void STATE_1_do(Ex1* sm)
{
    // No ancestor state handles `do` event.
    
    // STATE_1 behavior
    // uml: do TransitionTo(STATE_2)
    {
        // Step 1: Exit states until we reach `ROOT` state (Least Common Ancestor for transition).
        STATE_1_exit(sm);
        
        // Step 2: Transition action: ``.
        
        // Step 3: Enter/move towards transition target `STATE_2`.
        STATE_2_enter(sm);
        
        // Step 4: complete transition. Ends event dispatch. No other behaviors are checked.
        sm->state_id = Ex1_StateId_STATE_2;
        // No ancestor handles event. Can skip nulling `ancestor_event_handler`.
        return;
    } // end of behavior for STATE_1
}


////////////////////////////////////////////////////////////////////////////////
// event handlers for state STATE_2
////////////////////////////////////////////////////////////////////////////////

static void STATE_2_enter(Ex1* sm)
{
    // setup trigger/event handlers
    sm->current_state_exit_handler = STATE_2_exit;
}

static void STATE_2_exit(Ex1* sm)
{
    // adjust function pointers for this state's exit
    sm->current_state_exit_handler = ROOT_exit;
}


// Thread safe.
char const * Ex1_event_id_to_string(Ex1_EventId id)
{
    switch (id)
    {
        case Ex1_EventId_DO: return "DO";
        default: return "?";
    }
}
