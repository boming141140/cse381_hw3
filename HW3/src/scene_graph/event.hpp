#pragma once

namespace W3D
{

/*
* The EventType, MouseButton, KeyCode, KeyAction, MouseAction,
* Event, ResizeEvent KeyPressEvent, MouseInputEvent types defined
* below are for us to manage user input and provide the appropriate
* responses.
*/

// WE CARE ABOUT THREE BROAD TYPES OF EVENTS
enum class EventType
{
	eKeyInput,
	eMouseButton,
	eResize
};

// THE POSSIBLE MOUSE BUTTONS WE WILL RESPOND DO
enum class MouseButton
{
	eLeft,
	eRight,
	eMiddle,
	eUnknown
};

// THE POSSIBLE KEYBOARD KEYS WE WILL RESPOND TO
enum class KeyCode
{
	eUnknown,

	eW,
	eS,
	eA,
	eD,

	e1, // Player 1
	e2, // Player 2
	e3,	// Camera
	e4,	// Light 1
	e5, // Light 2
	e6, // Light 3
	e7, // Light 4
	e8, // Player 3
	e9, // Player 4
	e0, // Player 5

	eR,        // New entry for R
	eQ,        // New entry for Q
	eF,
};

// THERE ARE FOUR DIFFERENT TYPES OF KEYBOARD KEY INTERACTIONS
enum class KeyAction
{
	eDown,
	eUp,
	eRepeat,
	eUnknown
};

// THERE ARE FOUR DIFFERENT TYPES OF MOUSE BUTTON INTERACTIONS
enum class MouseAction
{
	eDown,
	eUp,
	eMove,
	eUnknown
};

// Event OBJECTS WILL STORE INFORMATION ABOUT A GIVEN EVENT, i.e. USER INTERACTION
struct Event
{
	Event(EventType type) :
	    type(type){};
	EventType type;
};

// FOR WHEN THE USER RESIZES THE WINDOW
struct ResizeEvent : Event
{
	ResizeEvent() :
	    Event(EventType::eResize){};
};

// FOR WHEN THE USER PRESSES/RELEASES A KEYBOARD KEY
struct KeyInputEvent : Event
{
	KeyInputEvent(KeyCode code, KeyAction action) :
	    Event(EventType::eKeyInput),
	    code(code),
	    action(action)
	{
	}
	KeyCode   code;
	KeyAction action;
};

// FOR WHEN THE USER PRESSES/RELEASES/MOVES THE MOUSE
struct MouseButtonInputEvent : Event
{
	MouseButtonInputEvent(MouseButton button, MouseAction action, float pos_x, float pos_y) :
	    Event(EventType::eMouseButton),
	    button(button),
	    action(action),
	    xpos(pos_x),
	    ypos(pos_y)
	{
	}
	MouseButton button;
	MouseAction action;
	float       xpos;
	float       ypos;
};

}        // namespace W3D