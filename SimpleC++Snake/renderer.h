#ifndef RENDERER_H
#define RENDERER_H

#include "utilities.h"

extern float widthPercent;
extern float heightPercent;
extern float startXPercent;
extern float startYPercent;

extern int rendererMin;
extern int rendererMax;

void renderBackground();

void updateVars();

void renderTilemap(std::array<std::array<uint32, tilemapSizeY>, tilemapSizeX>& tilemap);

void clearScreen(uint32 color);

void drawRectInPixels(int x0, int y0, int x1, int y1, uint32 color);

void drawRectInPercent(float x0, float y0, float x1, float y1, uint32 color);

#endif