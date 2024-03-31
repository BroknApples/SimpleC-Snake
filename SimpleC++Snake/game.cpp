#include "game.h"

#include <Windows.h>

// add object manager;
ObjectManager objectManager;

auto& player(objectManager.addObject<PlayerObject>(BEAUTIFULBLUE));
auto& score(objectManager.addObject<ScoreObject>());

Game::Game(HWND* window, HDC* hdc) {
	this->window = window;
	this->hdc = hdc;

	paused = false;

	for (int i = 0; i < tilemapSizeX; i++) {
		for (int j = 0; j < tilemapSizeY; j++) {
			tilemap[i][j] = calculateTileColor(i, j);
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
	if (PeekMessage(&message, *window, 0, 0, PM_REMOVE)) {
		// userInput
		for (int i = 0; i < BUTTON_COUNT; i++) { // resets changed to false;
			inputs.buttons[i].changed = false;
		}

		switch (message.message) {
			case WM_KEYUP:
			case WM_KEYDOWN: {
				uint32 vk_code = static_cast<uint32>(message.wParam);
				bool is_down = ((message.lParam & (1 << 31)) == 0);

				inputProcessing(vk_code, is_down);
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
	updateVelocityFromInputs(player);

	objectManager.update();
}

void Game::draw() {
	clearScreen(0x0f3814);

	renderTilemap(tilemap);
	objectManager.draw();

	StretchDIBits(*hdc, 0, 0, renderer.width, renderer.height, 0, 0, renderer.width, renderer.height,
		renderer.memory, &renderer.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
}