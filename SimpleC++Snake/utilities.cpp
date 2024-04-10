#include "utilities.h"

//******************Structs/Classes******************

//******************Structs/Classes******************


//******************Functions******************
uint32 calculateTileColor(const int xPos, const int yPos) {
	if ((xPos % 2) == (yPos % 2)) return LIGHTGREEN;
	else			  return SLIGHTLYDARKGREEN;
}

int getFPS() {
	std::ifstream readFile;
	std::string settings = "settings.txt";

	short frames;

	readFile.open(settings);
	if (!readFile.is_open()) {
		frames = 60;
	}
	else {
		readFile >> frames;
	}

	readFile.close();

	return frames;
}

bool getTickState() {
	bool val;
	(runNumber % static_cast<int>(1.0f / velocityScaleX) == 0) ? val = true : val = false;
	return val;
}
//******************Functions******************

//******************Global Variables******************
RenderState renderer = { NULL };
bool running = true;
float scale = 0.2f;
float velocityScaleX = 0.2f;
float velocityScaleY = velocityScaleX;
std::array<std::array<uint32, tilemapSizeY>, tilemapSizeX> tilemap = { NULL };
uint32 runNumber = 0;
//******************Global Variables******************