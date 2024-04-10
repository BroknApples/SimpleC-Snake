#ifndef GAME_H
#define GAME_H

#include "utilities.h"
#include "renderer.h"
#include "platform_commands.h"
#include "object_manager.h"

class Game {

private:
	ObjectManager* objectManager;
	FoodObject* food;
	PlayerObject* player;
	ScoreObject* score;

	HWND* window;
	HDC* hdc;
	int finalScore;

public:
	Game(HWND* window, HDC* hdc, ObjectManager* objectManager, FoodObject* food, PlayerObject* player, ScoreObject* score);
	~Game();

	inline int getScore() { return finalScore; }

	void init();

	void gameOver();

	void input(); // user inputs
	void update(); // game logic and input-based changes
	void draw(); // render to screen
};


#endif