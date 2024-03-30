#include "platform_commands.h"

void inputProcessing(uint32 vk_code, bool is_down) {
	switch (vk_code) {
		case VK_UP:
		case VK_W:
			inputs.buttons[BUTTON_MOVEUP].is_down = is_down;
			inputs.buttons[BUTTON_MOVEUP].changed = true;
			break;

		case VK_LEFT:
		case VK_A:
			inputs.buttons[BUTTON_MOVELEFT].is_down = is_down;
			inputs.buttons[BUTTON_MOVELEFT].changed = true;
			break;

		case VK_DOWN:
		case VK_S:
			inputs.buttons[BUTTON_MOVEDOWN].is_down = is_down;
			inputs.buttons[BUTTON_MOVEDOWN].changed = true;
			break;

		case VK_D:
		case VK_RIGHT:
			inputs.buttons[BUTTON_MOVERIGHT].is_down = is_down;
			inputs.buttons[BUTTON_MOVERIGHT].changed = true;
			break;
	}
}

void updateVelocityFromInputs(PlayerObject& player) {
	int xVel;
	int yVel;

	// move up
	if (PRESSED(BUTTON_MOVEUP)) {
		if (player.getYVelocity() < 0) return;
		xVel = 0;
		yVel = 1;
	}
	// move left
	else if (PRESSED(BUTTON_MOVELEFT)) {
		if (player.getXVelocity() > 0) return;
		xVel = -1;
		yVel = 0;
	}
	// move down
	else if (PRESSED(BUTTON_MOVEDOWN)) {
		if (player.getYVelocity() > 0) return;
		xVel = 0;
		yVel = -1;
	}
	// move right
	else if (PRESSED(BUTTON_MOVERIGHT)) {
		if (player.getXVelocity() < 0) return;
		xVel = 1;
		yVel = 0;
	}
	else {
		return;
	}

	player.updateVelocity(xVel, yVel);
}

Input inputs = { false };