// Autogenerated with StateSmith
#include "blinky1_printf_sm.h"
// this ends up in the generated c file
#include "app_timer.h"
#include "led.h"
#include <stdbool.h> // required for `consume_event` flag
#include <string.h> // for memset

static void ROOT_enter(blinky1_printf_sm* self);
static void ROOT_exit(blinky1_printf_sm* self);

static void LED_OFF_enter(blinky1_printf_sm* self);
static void LED_OFF_exit(blinky1_printf_sm* self);
static void LED_OFF_do(blinky1_printf_sm* self);

static void LED_ON_enter(blinky1_printf_sm* self);
static void LED_ON_exit(blinky1_printf_sm* self);
static void LED_ON_do(blinky1_printf_sm* self);

void blinky1_printf_sm_ctor(blinky1_printf_sm* self) {
  memset(self, 0, sizeof(*self));
}

void blinky1_printf_sm_start(blinky1_printf_sm* self) {
  ROOT_enter(self);
  // Transition to target state LED_OFF
  {
    // target state LED_OFF is a child of this state. No need to exit this state.
    
    // Enter towards target
    LED_OFF_enter(self);
    
    // update state_id
    self->state_id = BLINKY1_PRINTF_SM_STATE_ID_LED_OFF;
  } // end of transition code
}

void blinky1_printf_sm_dispatch_event(blinky1_printf_sm* self, enum blinky1_printf_sm_event_id event_id) {
  blinky1_printf_sm_func behavior_func = self->current_event_handlers[event_id];
  
  while (behavior_func != NULL) {
    self->ancestor_event_handler = NULL;
    behavior_func(self);
    behavior_func = self->ancestor_event_handler;
  }
}

const char* blinky1_printf_sm_state_id_to_string(const enum blinky1_printf_sm_state_id id) {
  switch (id) {
    case BLINKY1_PRINTF_SM_STATE_ID_ROOT: return "ROOT";
    case BLINKY1_PRINTF_SM_STATE_ID_LED_OFF: return "LED_OFF";
    case BLINKY1_PRINTF_SM_STATE_ID_LED_ON: return "LED_ON";
    default: return "?";
  }
}

////////////////////////////////////////////////////////////////////////////////
// event handlers for state ROOT
////////////////////////////////////////////////////////////////////////////////

static void ROOT_enter(blinky1_printf_sm* self) {
  // setup trigger/event handlers
  self->current_state_exit_handler = ROOT_exit;
}

static void ROOT_exit(blinky1_printf_sm* self) {
  // State machine root is a special case. It cannot be exited.
  (void)self;  // nothing to see here compiler. move along!
}


////////////////////////////////////////////////////////////////////////////////
// event handlers for state LED_OFF
////////////////////////////////////////////////////////////////////////////////

static void LED_OFF_enter(blinky1_printf_sm* self) {
  // setup trigger/event handlers
  self->current_state_exit_handler = LED_OFF_exit;
  self->current_event_handlers[BLINKY1_PRINTF_SM_EVENT_ID_DO] = LED_OFF_do;
  
  // state behavior:
  {
    // uml action: turn_led_off();
    led_turn_off();;
  } // end of behavior code
  
  // state behavior:
  {
    // uml action: reset_timer();
    self->vars.timer_started_at_ms = app_timer_get_ms();
  } // end of behavior code
}

static void LED_OFF_exit(blinky1_printf_sm* self) {
  // adjust function pointers for this state's exit
  self->current_state_exit_handler = ROOT_exit;
  self->current_event_handlers[BLINKY1_PRINTF_SM_EVENT_ID_DO] = NULL;  // no ancestor listens to this event
}

static void LED_OFF_do(blinky1_printf_sm* self) {
  // setup handler for next ancestor that listens to `do` event
  self->ancestor_event_handler = NULL; // no ancestor state handles `do` event
  
  // state behavior:
  {
    // Note: no `consume_event` variable possible here because of state transition. The event must be consumed.
    // uml guard: after_ms(500)
    // uml transition target: LED_ON
    if (( (app_timer_get_ms() - self->vars.timer_started_at_ms) >= 500 )) {
      // Transition to target state LED_ON
      {
        // First, exit up to Least Common Ancestor ROOT.
        while (self->current_state_exit_handler != ROOT_exit) {
          self->current_state_exit_handler(self);
        }
        
        // Enter towards target
        LED_ON_enter(self);
        
        // update state_id
        self->state_id = BLINKY1_PRINTF_SM_STATE_ID_LED_ON;
      } // end of transition code
      
      // Mark event as handled. Required because of transition.
      // self->ancestor_event_handler = NULL; // already done at top of function
      return; // event processing immediately stops when a transition occurs. No other behaviors for this state are checked.
    } // end of guard code
  } // end of behavior code
}

////////////////////////////////////////////////////////////////////////////////
// event handlers for state LED_ON
////////////////////////////////////////////////////////////////////////////////

static void LED_ON_enter(blinky1_printf_sm* self) {
  // setup trigger/event handlers
  self->current_state_exit_handler = LED_ON_exit;
  self->current_event_handlers[BLINKY1_PRINTF_SM_EVENT_ID_DO] = LED_ON_do;
  
  // state behavior:
  {
    // uml action: turn_led_on();
    //             reset_timer();
    led_turn_on();;
    self->vars.timer_started_at_ms = app_timer_get_ms();
  } // end of behavior code
}

static void LED_ON_exit(blinky1_printf_sm* self) {
  // adjust function pointers for this state's exit
  self->current_state_exit_handler = ROOT_exit;
  self->current_event_handlers[BLINKY1_PRINTF_SM_EVENT_ID_DO] = NULL;  // no ancestor listens to this event
}

static void LED_ON_do(blinky1_printf_sm* self) {
  // setup handler for next ancestor that listens to `do` event
  self->ancestor_event_handler = NULL; // no ancestor state handles `do` event
  
  // state behavior:
  {
    // Note: no `consume_event` variable possible here because of state transition. The event must be consumed.
    // uml guard: elapsed_ms > 1000
    // uml transition target: LED_OFF
    if ((app_timer_get_ms() - self->vars.timer_started_at_ms) > 1000) {
      // Transition to target state LED_OFF
      {
        // First, exit up to Least Common Ancestor ROOT.
        while (self->current_state_exit_handler != ROOT_exit) {
          self->current_state_exit_handler(self);
        }
        
        // Enter towards target
        LED_OFF_enter(self);
        
        // update state_id
        self->state_id = BLINKY1_PRINTF_SM_STATE_ID_LED_OFF;
      } // end of transition code
      
      // Mark event as handled. Required because of transition.
      // self->ancestor_event_handler = NULL; // already done at top of function
      return; // event processing immediately stops when a transition occurs. No other behaviors for this state are checked.
    } // end of guard code
  } // end of behavior code
}

