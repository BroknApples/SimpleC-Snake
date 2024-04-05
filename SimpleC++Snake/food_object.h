#ifndef FOOD_OBJECT_H
#define FOOD_OBJECT_H

#include "object_manager.h"

class FoodObject : public WorldObject {
	
private:
	int xPos;
	int yPos;

	uint32 color;

	bool eaten;

	int pointValue;
	int totalPoints;

public:
	FoodObject(uint32 color, int pointValue);

	inline int getPoints() { return totalPoints; }
	inline int getEatenState() { return eaten; }

	void init() override;
	void update() override;
	void draw() override;

	void checkCollision(int xPos, int yPos, uint32 color) override;

	void getNewPosition();
};

#endif