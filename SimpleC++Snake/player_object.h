#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H

#include "utilities.h"
#include "object_manager.h"


// Each new length of snake added
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

	void update(int xVel, int yVel);
	void draw();
};

// Linked List of segments
struct SegmentList {
	std::unique_ptr<PlayerSegment> segment;

	int pastXVel = 0;
	int pastYVel = 0;

	std::shared_ptr<SegmentList> next;
};

// Player character
class PlayerObject : public WorldObject {

private:
	std::shared_ptr<SegmentList> segmentsHead;

	int xVelocity;
	int yVelocity;

	uint32 spriteColor;

public:
	PlayerObject();
	PlayerObject(uint32 spriteColor);
	~PlayerObject();

	inline int getXVelocity() { return xVelocity; }
	inline int getYVelocity() { return yVelocity; }
	inline void updateVelocity(const int xVelocity, const int yVelocity) {
		this->xVelocity = xVelocity;
		this->yVelocity = yVelocity;
	}

	void addSegment();

	void init() override;
	void update() override;
	void draw() override;
};

#endif