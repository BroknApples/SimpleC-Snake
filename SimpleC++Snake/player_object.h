#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H

#include "utilities.h"
#include "object_manager.h"

class PlayerSegment {

private:
	int xPos;
	int yPos;
	
	uint32 color;

public:
	PlayerSegment(int xPos, int yPos, uint32 color);

	inline int getX() const { return xPos; }
	inline int getY() const { return yPos; }
	inline uint32 getColor() const { return color; }
	inline void updateX(int newX) { 
		xPos += newX;
		xPos = clamp(0, xPos, tilemapSizeX - 1);
	}
	inline void updateY(int newY) { 
		yPos += newY;
		yPos = clamp(0, yPos, tilemapSizeY - 1);
	}
};

class PlayerObject : public WorldObject {

private:
	std::vector<std::shared_ptr<PlayerSegment>> segments;

	int xVelocity;
	int yVelocity;

	uint32 spriteColor;

public:
	PlayerObject();
	PlayerObject(uint32 spriteColor);
	~PlayerObject();

	inline void init() override { 
		addSegment(1, 1);
		id = getNewObjectID();
	}

	void update();

	void addSegment(int xPos, int yPos);
};

#endif