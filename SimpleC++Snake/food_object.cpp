#include "food_object.h"

FoodObject::FoodObject(uint32 color, int pointValue) {
	xPos = 0;
	yPos = 0;

	eaten = false;

	this->color = color;

	this->pointValue = pointValue;
	totalPoints = 0;
}

void FoodObject::getNewPosition() {
	// generate 2 random numbers for new position of the food
	srand(time(NULL));

	int newXPos;
	int newYPos;
	do {
		// for some reason there is an exception when placing a new food occasionally
		newXPos = rand() % (tilemapSizeX - 1);
		newYPos = rand() % (tilemapSizeY - 1);
	} while (tilemap[newXPos][newYPos] != calculateTileColor(newXPos, newYPos));

	xPos = newXPos;
	yPos = newYPos;
}


void FoodObject::init() {
	xPos = tilemapSizeX - (tilemapSizeX / 4);

	int halfY;
	if (tilemapSizeY % 2 == 0) halfY = tilemapSizeY / 2;
	else					   halfY = (tilemapSizeY / 2) + 1;
	yPos = halfY;
}

void FoodObject::update() {
	eaten = false;
	checkCollision(xPos, yPos, color);

	if (eaten) {
		// reset position to its normal color
		tilemap[xPos][yPos] = calculateTileColor(xPos, yPos);

		getNewPosition();
		totalPoints++;
	}
}

void FoodObject::draw() {
	tilemap[xPos][yPos] = color;
}

void FoodObject::checkCollision(int xPos, int yPos, uint32 color) {
	if (tilemap[xPos][yPos] != color) {
		eaten = true;
	}
}