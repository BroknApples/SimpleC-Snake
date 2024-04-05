#ifndef FOOD_OBJECT_H
#define FOOD_OBJECT_H

#include "utilities.h"
#include "object_manager.h"

class FoodObject : public WorldObject {
	
private:
	int xPos;
	int yPos;

	uint32 color;

	bool eaten;

	int pointValue;

public:
	FoodObject(uint32 color, int pointValue);

	void init() override;
	void update() override;
	void draw() override;

	void checkCollision(int xPos, int yPos, uint32 color) override;

	void getNewPosition();
};

#endif