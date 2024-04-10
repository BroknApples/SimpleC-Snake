#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H

#include "object_manager.h"


// Each new length of snake added
class PlayerSegment {

private:
	float xPos;
	float yPos;

	uint32 color;

public:
	PlayerSegment(float xPos, float yPos, uint32 color);

	inline float getX() const { return xPos; }
	inline float getY() const { return yPos; }
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

	bool isDead;

	uint32 spriteColor;

public:
	PlayerObject();
	PlayerObject(uint32 spriteColor);
	~PlayerObject();

	inline std::shared_ptr<SegmentList> getSegmentsHead() { return segmentsHead; }
	inline int getXVelocity() const { return xVelocity; }
	inline int getYVelocity() const { return yVelocity; }
	inline uint32 getColor() const { return spriteColor; }
	inline bool getHealthState() const { return isDead; }

	inline void updateVelocity(const int xVelocity, const int yVelocity) {
		this->xVelocity = xVelocity;
		this->yVelocity = yVelocity;
	}

	void addSegment();
	void checkCollision(int xPos, int yPos, uint32 snakeColor) override;

	void init() override;
	void update() override;
	void draw() override;
};

#endif