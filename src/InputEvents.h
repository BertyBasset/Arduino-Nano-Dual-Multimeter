// (c)2018 Robin Griffiths
#ifndef _InputEvents_h
#define _InputEvents_h
#endif

#include "Arduino.h"

class InputEvents {
public:
	// Event Argument values for digital pins
	enum Events {
		LOW_TO_HIGH,
		HELD_HIGH,
		HIGH_TO_LOW,
		HOLD_RELEASE
	};

private:
	//                          PinNo PinState 
	void(*functionPointerDigital)(int, int);
	const static int NUM_MAX_DIGITAL_INPUT_EVENTS = 10;
	int numDigitalInputEventsAdded = 0;
	struct DigitalInputEvent {
		int pinNo;
		void (* callbackFunctionDigital)(int, int);		// CallbackFunction(int PinNumber, DigitalEventArgs EventArgs)
		int lastPinState;
		unsigned long timePinStateChanged;    // milliseconds
		bool heldEventRaised;
		bool DefaultSwitchState;
		int HELD_EVENT_RAISED_AFTER_MILLIS;
	};

	// Arrays to store registered events and their settings
	DigitalInputEvent digitalInputEvents[NUM_MAX_DIGITAL_INPUT_EVENTS];



public:
	// Processes all registered events, and calls their callback function if digital inpout changes
	void processEvents();

	// Registers Digital Input Callback function that accepts no parameters
	void registerDigitalInputEvent(int pinNum, void (* callbackFunctionDigital) (int, int), bool DefaultSwitchState = LOW, int holdTime = 1000);
};
