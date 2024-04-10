#include "platform_commands.h"

void getKeyStates(uint32& vk_code, bool& is_down, HWND* window) {
	MSG message;
	if (PeekMessage(&message, *window, 0, 0, PM_REMOVE)) {
		// userInput
		for (int i = 0; i < BUTTON_COUNT; i++) { // resets changed to false;
			inputs.buttons[i].changed = false;
		}

		switch (message.message) {
			case WM_KEYUP:
			case WM_KEYDOWN: {
				vk_code = static_cast<uint32>(message.wParam);
				is_down = ((message.lParam & (1 << 31)) == 0);
			} break;
		}

		TranslateMessage(&message);
		DispatchMessageA(&message);
	}
}

void inputProcessing(uint32 vk_code, bool is_down) {
	switch (vk_code) {
	//*****MOVEMENT*****
		case VK_UP:
		case VK_W:
			inputs.buttons[BUTTON_MOVEUP].is_down = is_down;
			if (!inputs.buttons[BUTTON_MOVEUP].changed) {
				inputs.buttons[BUTTON_MOVEUP].changed = true;
			}
			else {
				inputs.buttons[BUTTON_MOVEUP].changed = false;
			}
			break;

		case VK_LEFT:
		case VK_A:
			inputs.buttons[BUTTON_MOVELEFT].is_down = is_down;
			if (!inputs.buttons[BUTTON_MOVELEFT].changed) {
				inputs.buttons[BUTTON_MOVELEFT].changed = true;
			}
			else {
				inputs.buttons[BUTTON_MOVELEFT].changed = false;
			}
			break;

		case VK_DOWN:
		case VK_S:
			inputs.buttons[BUTTON_MOVEDOWN].is_down = is_down;
			if (!inputs.buttons[BUTTON_MOVEDOWN].changed) {
				inputs.buttons[BUTTON_MOVEDOWN].changed = true;
			}
			else {
				inputs.buttons[BUTTON_MOVEDOWN].changed = false;
			}
			break;

		case VK_D:
		case VK_RIGHT:
			inputs.buttons[BUTTON_MOVERIGHT].is_down = is_down;
			if (!inputs.buttons[BUTTON_MOVERIGHT].changed) {
				inputs.buttons[BUTTON_MOVERIGHT].changed = true;
			}
			else {
				inputs.buttons[BUTTON_MOVERIGHT].changed = false;
			}
			break;
	//*****MOVEMENT*****
	//*****MENU NAV*****
	}
}

void updateVelocityFromInputs(PlayerObject& player) {
	int xVel;
	int yVel;

	// move up
	if (PRESSED(BUTTON_MOVEUP)) {
		if (player.getSegmentsHead()->pastYVel < 0) return;

		xVel = 0;
		yVel = 1;
	}
	// move left
	else if (PRESSED(BUTTON_MOVELEFT)) {
		if (player.getSegmentsHead()->pastXVel > 0) return;

		xVel = -1;
		yVel = 0;
	}
	// move down
	else if (PRESSED(BUTTON_MOVEDOWN)) {
		if (player.getSegmentsHead()->pastYVel > 0) return;

		xVel = 0;
		yVel = -1;
	}
	// move right
	else if (PRESSED(BUTTON_MOVERIGHT)) {
		if (player.getSegmentsHead()->pastXVel < 0) return;

		xVel = 1;
		yVel = 0;
	}
	else {
		return;
	}

	player.updateVelocity(xVel, yVel);
}

Input inputs = { false };