// Analog Inputs - go through each registred analog input event

#include "InputEvents.h"
#include "Arduino.h"
#include <math.h>
//bool heldEventOccured = false;

void InputEvents::processEvents() {
  // HELD event is raised when pin has been at same state for this time period. Once fired, it will not fire again until state changed
  //const int HELD_EVENT_RAISED_AFTER_MILLIS = 1000;



  // Digital Inputs - go through each registred digital input event
  for (int i = 0; i < InputEvents::numDigitalInputEventsAdded; i++) {
    bool currentState = digitalRead(digitalInputEvents[i].pinNo);
   InputEvents::functionPointerDigital = digitalInputEvents[i].callbackFunctionDigital;
    // Check if digital input changed state                      V       Debounce       V
    if (currentState != digitalInputEvents[i].lastPinState && millis() - digitalInputEvents[i].timePinStateChanged > 5) {
      if(currentState == !digitalInputEvents[i].DefaultSwitchState)
        functionPointerDigital(digitalInputEvents[i].pinNo, InputEvents::LOW_TO_HIGH);
      else {
        // If held event has occured, don't send high to low
        //if(!heldEventOccured)
        if(!digitalInputEvents[i].heldEventRaised)
          functionPointerDigital(digitalInputEvents[i].pinNo, InputEvents::HIGH_TO_LOW);
        else
          functionPointerDigital(digitalInputEvents[i].pinNo, InputEvents::HOLD_RELEASE);
        //heldEventOccured = false;
        //digitalInputEvents[i].heldEventRaised = false;
      }
      digitalInputEvents[i].heldEventRaised = false;
      digitalInputEvents[i].timePinStateChanged = millis();
    } 
    

    else {
      // State has not changed
      // Check if held and raise event if so
      if (millis() - digitalInputEvents[i].timePinStateChanged > digitalInputEvents[i].HELD_EVENT_RAISED_AFTER_MILLIS) {
        if (!digitalInputEvents[i].heldEventRaised) {
          if (currentState == !digitalInputEvents[i].DefaultSwitchState) {
            functionPointerDigital(digitalInputEvents[i].pinNo, InputEvents::HELD_HIGH);
            //heldEventOccured = true;
          }
          //else
          //  functionPointerDigital(_digitalInputEvents[i].pinNo, Event::HELD_LOW);
          digitalInputEvents[i].heldEventRaised = true;
        }
      }
    }

    digitalInputEvents[i].lastPinState = currentState;
  }
}

// Registers event by addiing to Events array
void InputEvents::registerDigitalInputEvent(int pinNum, void (* callbackFunctionDigital)(int, int), bool defaultSwitchState, int holdTime) {
  pinMode(pinNum, INPUT);
  DigitalInputEvent event = { pinNum, callbackFunctionDigital, defaultSwitchState, millis(), false, defaultSwitchState, holdTime };
  InputEvents::digitalInputEvents[InputEvents::numDigitalInputEventsAdded] = event;
  InputEvents::numDigitalInputEventsAdded++;
}
