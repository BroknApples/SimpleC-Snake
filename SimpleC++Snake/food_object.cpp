#include "food_object.h"

FoodObject(uint32 color, int pointValue) {
	this->color = color;
	int foodValue = pointValue;
}

void FoodObject::getNewPosition() {
	// generate 2 random numbers for new position of the food
	srand(time(NULL));

	int newXPos;
	int newYPos;
	do {
		newXPos = rand() % tilemapSizeX;
		newYPos = rand() % tilemapSizeY;
	} while (tilemap[newXPos][newYPos] != calculateTileColor(newXPos, newYPos));

	xPos = newXPos;
	yPos = newYPos;
}


void FoodObject::init() {
	
}

void FoodObject::update() {
	if (eaten) {
		tilemap[xPos][yPos] = calculateTileColor(xPos, yPos);
		getNewPosition();
	}
}

void FoodObject::draw() {
	tilemap[xPos][yPos] = color;
}

void checkCollision(int xPos, int yPos, uint32 color) {
	if (tilemap[xPos][yPos] != calculateTileColor(xPos, yPos)) {

	}
}