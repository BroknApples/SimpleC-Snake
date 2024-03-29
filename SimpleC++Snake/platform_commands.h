#ifndef PLATFORM_COMMANDS_H
#define PLATFORM_COMMANDS_H

#include "utilities.h"
#include "renderer.h"

struct Input;

struct ButtonState {
	bool is_down = 0;
	bool changed = 0;
};

enum { // holds every button action in the game
	BUTTON_MOVEUP,
	BUTTON_MOVEDOWN,
	BUTTON_MOVELEFT,
	BUTTON_MOVERIGHT,
	BUTTON_PAUSE,
	BUTTON_LEFTCLICK,
	BUTTON_RIGHTCLICK,
	BUTTON_GOBACK,

	// how many buttons actions there are in total
	BUTTON_COUNT 
};

struct Input {
	std::array<ButtonState, BUTTON_COUNT> buttons;
};


void inputProccessing(uint32 vk_code, bool is_down);
void updateFromInputs();

extern Input inputs;

#endif