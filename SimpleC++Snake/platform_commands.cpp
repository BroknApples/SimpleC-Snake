#include "platform_commands.h"

void inputProccessing(uint32 vk_code, bool is_down) {
	switch (vk_code) {

	case VK_W:
		inputs.buttons[BUTTON_MOVEUP].is_down = is_down;
		inputs.buttons[BUTTON_MOVEUP].changed = true;
	}
}

void updateFromInputs() {
	if (IS_DOWN(BUTTON_MOVEUP) || PRESSED(BUTTON_MOVEUP)) {
		std::cout << "Moved up!\n";
	}
}

Input inputs = { false };