#include "game.h"

#include <Windows.h>

// add object manager;
ObjectManager objectManager;

auto& player(objectManager.addObject<PlayerObject>());
auto& score(objectManager.addObject<ScoreObject>());

Game::Game(HWND* window, HDC* hdc) {
	this->window = window;
	this->hdc = hdc;

	paused = false;

	for (int i = 0; i < tilemapSizeX; i++) {
		for (int j = 0; j < tilemapSizeY; j++) {
			if ((i % 2) == (j % 2)) {
				tilemap[i][j] = 0x007a21;
			}
			else {
				tilemap[i][j] = 0x00b515;
			}
		}
	}
}

Game::~Game() {}

void Game::init() {
	player.init();
	score.init();
}

void Game::pause() {
	bool unpause = false;

	while (!unpause) {
		// check if user presses unpause key or clicks resume button
	}
}

void Game::input() {
	MSG message;
	while (PeekMessage(&message, *window, 0, 0, PM_REMOVE)) {
		// userInput
		for (int i = 0; i < BUTTON_COUNT; i++) {
			inputs.buttons[i].changed = false;
		}

		switch (message.message) {
			case WM_KEYUP:
			case WM_KEYDOWN: {
				uint32 vk_code = static_cast<uint32>(message.wParam);
				bool is_down = ((message.lParam & (1 << 32)) == 0);

				inputProccessing(vk_code, is_down);
			} break;
			default: {
				break;
			}
		}

		TranslateMessage(&message);
		DispatchMessageA(&message);
	}
}

void Game::update() {
	// hit detection, number generators, input-based changes, etc.
	objectManager.update();
	updateFromInputs();
}

void Game::draw() {
	clearScreen(0x0f3814);

	renderTilemap(tilemap);


	StretchDIBits(*hdc, 0, 0, renderer.width, renderer.height, 0, 0, renderer.width, renderer.height,
		renderer.memory, &renderer.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
}