#include "player_object.h"

PlayerSegment::PlayerSegment(int xPos, int yPos, uint32 color) {
	this->xPos = xPos;
	this->yPos = yPos;
	this->color = color;
}

//************************************************************************
//************************************************************************


PlayerObject::PlayerObject() {
	xVelocity = velocityScale;
	yVelocity = 0 * velocityScale;

	spriteColor = 0x4c3228;
}

PlayerObject::PlayerObject(uint32 spriteColor) {
	xVelocity = velocityScale;
	yVelocity = 0 * velocityScale;

	this->spriteColor = spriteColor;
}

PlayerObject::~PlayerObject() {}

void PlayerObject::addSegment(int xPos, int yPos) {
	auto segment = std::make_shared<PlayerSegment>(xPos, yPos, spriteColor);
	segments.emplace_back(std::move(segment));
}


void PlayerObject::update() {
	for (auto& segment : segments) {
		segment->updateX(xVelocity);
		segment->updateY(yVelocity);

		//update tilemap
		const int x = segment->getX();
		const int y = segment->getY();
		tilemap[x][y] = segment->getColor();
	}
}