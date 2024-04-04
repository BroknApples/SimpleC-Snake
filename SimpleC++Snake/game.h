#ifndef GAME_H
#define GAME_H

#include "utilities.h"
#include "renderer.h"
#include "platform_commands.h"
#include "object_manager.h"

class Game {

private:
	HWND* window;
	HDC* hdc;
	bool paused;

public:
	Game(HWND* window, HDC* hdc);
	~Game();

	void init();

	void pause();
	void gameOver();

	void input(); // user inputs
	void update(); // game logic and input-based changes
	void draw(); // render to screen
};


#endif