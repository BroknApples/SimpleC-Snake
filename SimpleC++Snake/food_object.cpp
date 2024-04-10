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
		newXPos = rand() % (tilemapSizeX);
		newYPos = rand() % (tilemapSizeY);
	} while (tilemap[newXPos][newYPos] != calculateTileColor(newXPos, newYPos));


	//***************DATA COLLECTION***************
	std::ofstream writeFile;
	writeFile.open("food_positions.txt", std::ofstream::app);
	writeFile << "(" << newXPos << ", " << newYPos << ")\n";
	writeFile.close();
	//***************DATA COLLECTION***************

	xPos = newXPos;
	yPos = newYPos;
}


void FoodObject::init() {
	xPos = tilemapSizeX - (tilemapSizeX / 4) - 1;

	int halfY;
	if (tilemapSizeY % 2 == 0) halfY = (tilemapSizeY / 2) + 1;
	else					   halfY = (tilemapSizeY / 2);
	yPos = halfY;

	//***************DATA COLLECTION***************
	std::ofstream writeFile;
	writeFile.open("food_positions.txt", std::ofstream::app);
	writeFile << "(" << xPos << ", " << yPos << ")\n";
	writeFile.close();
	//***************DATA COLLECTION***************
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