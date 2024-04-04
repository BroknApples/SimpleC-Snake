#include "renderer.h"

extern float widthPercent = 0;
extern float heightPercent = 0;
extern float startXPercent = 0;
extern float startYPercent = 0;

extern int rendererMin = 0;
extern int rendererMax = 0;

void renderBackground() {
	// Tilemap Border
	drawRectInPercent(startXPercent - 2.5f,
					  startYPercent - 2.5f,
					  startXPercent + (tilemapSizeX * widthPercent)  + 2.5f,
					  startYPercent + (tilemapSizeY * heightPercent) + 2.5f,
					  DARKERGREEN);
	// Game Header Bar
	drawRectInPercent(0.0f, 95.0f, 100.0f, 100.0f, DARKESTGREEN);
}

void updateVars() {
	rendererMin = min(renderer.width, renderer.height);
	rendererMax = max(renderer.width, renderer.height);
	// Width and height of each square
	widthPercent = 95.0f / tilemapSizeX;
	heightPercent = 90.0f / tilemapSizeY;

	// Percent of the screen we should start renderering at
	startXPercent = 0.0f;
	startYPercent = 0.0f;

	if (renderer.width > renderer.height) {
		startXPercent = (static_cast<float>(rendererMax - rendererMin) / (2 * rendererMin)) * 100.0f;
		startYPercent = 0.0f;
	}
	else {
		startXPercent = 0.0f;
		startYPercent = (static_cast<float>(rendererMax - rendererMin) / (2 * rendererMin)) * 100.0f;
	}

	// Convert startX, startY, width, and height percent to be scaled based
	// on the renderer.width and renderer.height, not the rendererMin of the two
	widthPercent = ((widthPercent * rendererMin) / renderer.width);
	heightPercent = ((heightPercent * rendererMin) / renderer.height);

	startXPercent = ((startXPercent * rendererMin) / renderer.width) + 2.5f;
	startYPercent = ((startYPercent * rendererMin) / renderer.height) + 2.5f;
}

void renderTilemap(std::array<std::array<uint32, tilemapSizeY>, tilemapSizeX>& tilemap) {
	for (int i = 0; i < tilemapSizeX; i++) {
		for (int j = 0; j < tilemapSizeY; j++) {
			drawRectInPercent(startXPercent + (i * widthPercent),
							  startYPercent + (j * heightPercent),
							  startXPercent + ((i + 1) * widthPercent),
							  startYPercent + ((j + 1) * heightPercent),
							  tilemap[i][j]);
		}
	}
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

void drawRectInPercent(float x0, float y0, float x1, float y1, uint32 color) {
	// clamp value between 0 and 100
	x0 = clamp(0, x0, 100);
	y0 = clamp(0, y0, 100);
	x1 = clamp(0, x1, 100);
	y1 = clamp(0, y1, 100);

	// change value to a percentage
	x0 *= 0.01f;
	y0 *= 0.01f;
	x1 *= 0.01f;
	y1 *= 0.01f;

	int pixelX0 = static_cast<int>(static_cast<float>(renderer.width)  * x0);
	int pixelY0 = static_cast<int>(static_cast<float>(renderer.height) * y0);
	int pixelX1 = static_cast<int>(static_cast<float>(renderer.width)  * x1);
	int pixelY1 = static_cast<int>(static_cast<float>(renderer.height) * y1);

	// possible change this to consider the rendererMax and rendererMin of the same axis to allow for
	// renderering something with bounds such as (50, 50, 25, 25, COLOR) instead of only (25, 25, 50, 50, COLOR)
	drawRectInPixels(pixelX0, pixelY0, pixelX1, pixelY1, color);
}