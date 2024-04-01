#ifndef FOOD_OBJECT_H
#define FOOD_OBJECT_H

#include "object_manager.h"
#include "utilities.h"

class FoodObject : public WorldObject {

private:
	int xPos;
	int yPos;

	const int foodValue = 1;

public:
	void init() override;
	void update() override;
	void draw() override;

	void addNewFood();
};

#endif