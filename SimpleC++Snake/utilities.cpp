#include "utilities.h"

//******************Structs/Classes******************

//******************Structs/Classes******************


//******************Functions******************
uint32 calculateTileColor(const int xPos, const int yPos) {
	if ((xPos % 2) == (yPos % 2)) return LIGHTGREEN;
	else			  return DARKGREEN;
}
//******************Functions******************

//******************Global Variables******************
RenderState renderer = { NULL };
bool running = true;
float scale = 0.01f;
int velocityScaleX = 1;
int velocityScaleY = 1;
std::array<std::array<uint32, tilemapSizeY>, tilemapSizeX> tilemap = { NULL };
//******************Global Variables******************