#ifndef RENDERER_H
#define RENDERER_H

#include "utilities.h"

static int leftWall;
static int rightWall;
static int bottomWall;
static int topWall;

void renderTilemap(std::array<std::array<uint32, tilemapSizeY>, tilemapSizeX> tilemap);

void clearScreen(uint32 color);

void drawRectInPixels(int x0, int y0, int x1, int y1, uint32 color);

void drawRect(float x, float y, float halfX, float halfY, uint32 color);

#endif