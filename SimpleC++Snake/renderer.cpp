#include "renderer.h"

// *pixel++ = static_cast<uint32>(sqrt((x * x) + (y * y)) / 9); looks cool ig

void renderTilemap(std::array<std::array<uint32, tilemapSizeY>, tilemapSizeX> tilemap) {
	int min = min(renderer.height, renderer.width);
	int max = max(renderer.height, renderer.width);

	int tilePixelLengthX = min / tilemapSizeX;
	int tilePixelLengthY = min / tilemapSizeY;

	int startX;
	int startY;
	if (renderer.width > renderer.height) {
		startX = (max - min) / 2;
		startY = 0;
	}
	else {
		startX = 0;
		startY = (max - min) / 2;
	}

	int remainderX = renderer.width % tilePixelLengthX;
	int remainderY = renderer.height % tilePixelLengthY;

	for (int i = 0; i < tilemapSizeX; i++) {
		for (int j = 0; j < tilemapSizeY; j++) {
			drawRectInPixels((i * tilePixelLengthX) + startX + (remainderX / 2),
							 (j * tilePixelLengthY) + startY + (remainderY / 2),
							 (i * tilePixelLengthX) + startX + (remainderX / 2) + tilePixelLengthX,
							 (j * tilePixelLengthY) + startY + (remainderY / 2) + tilePixelLengthY,
							 tilemap[i][j]);
		}
	}

	leftWall   = startX;
	rightWall  = startY;
	bottomWall = startX + (tilemapSizeX * tilePixelLengthX);
	topWall    = startY + (tilemapSizeY * tilePixelLengthY);
}

void clearScreen(uint32 color) {
	uint32* pixel = static_cast<uint32*>(renderer.memory);
	for (int x = 0; x < renderer.width; x++) {
		for (int y = 0; y < renderer.height; y++) {
			*pixel++ = color;
		}
	}
}

void drawRectInPixels(int x0, int y0, int x1, int y1, uint32 color) {
	x0 = clamp(0, x0, renderer.width);
	x1 = clamp(0, x1, renderer.width);
	y0 = clamp(0, y0, renderer.height);
	y1 = clamp(0, y1, renderer.height);


	for (int y = y0; y < y1; y++) {
		uint32* pixel = static_cast<uint32*>(renderer.memory) + x0 + y * renderer.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}
}

void drawRect(float x, float y, float half_x, float half_y, uint32 color) {
	// Maintain relative position
	x	  *= renderer.height;
	half_x *= renderer.height;
	y	  *= renderer.height;
	half_y *= renderer.height;

	x += static_cast<float>(renderer.width) / 2.0f;
	y += static_cast<float>(renderer.height) / 2.0f;

	//Change percent value to pixels;
	int x0 = static_cast<int>(x - half_x);
	int x1 = static_cast<int>(x + half_y);
	int y0 = static_cast<int>(y - half_x);
	int y1 = static_cast<int>(y + half_y);

	drawRectInPixels(x0, y0, x1, y1, color);
}