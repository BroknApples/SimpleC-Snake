#include "game.h"

#include <Windows.h>

Game::Game(HWND* window, HDC* hdc, ObjectManager* objectManager, FoodObject* food, PlayerObject* player, ScoreObject* score) {
	this->window = window;
	this->hdc = hdc;

	this->objectManager = objectManager;
	this->food = food;
	this->player = player;
	this->score = score;

	finalScore = 0;
	running = true;

	for (int i = 0; i < tilemapSizeX; i++) {
		for (int j = 0; j < tilemapSizeY; j++) {
			tilemap[i][j] = calculateTileColor(i, j);
		}
	}
}

Game::~Game() {}

void Game::init() {
	updateVars();
	objectManager->init();

	for (int i = 0; i < 3; i++)
		player->addSegment();
}

void Game::gameOver() {
	finalScore = score->getScore();
	renderScore(window, finalScore);
	running = false;
}

void Game::draw() {
	clearScreen(0x000000);
	renderBackground();
	renderTilemap(tilemap);

	objectManager->draw();

	StretchDIBits(*hdc, 0, 0, renderer.width, renderer.height, 0, 0, renderer.width, renderer.height,
		renderer.memory, &renderer.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
}

void Game::input() {
	uint32 vk_code;
	bool is_down;

	getKeyStates(vk_code, is_down, window);
	inputProcessing(vk_code, is_down);
}

void Game::update() {
	updateVars();

	// If the snake has collided with something other than food
	if (player->getHealthState()) {
		gameOver();
	}
	
	updateVelocityFromInputs(*player);

	// Update all entities
	objectManager->update();
	if (food->getEatenState()) {
		player->addSegment();
	}

	score->setScore(food->getPoints());
}