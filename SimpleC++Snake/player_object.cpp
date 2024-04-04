#include "player_object.h"

PlayerSegment::PlayerSegment(float xPos, float yPos, uint32 color) {
	this->xPos = xPos;
	this->yPos = yPos;
	this->color = color;
}

void PlayerSegment::update(int xVel, int yVel) {
	xPos += (static_cast<float>(xVel) * velocityScaleX);
	xPos = clamp(0, xPos, tilemapSizeX - 1);
	yPos += (static_cast<float>(yVel) * velocityScaleY);
	yPos = clamp(0, yPos, tilemapSizeY - 1);
}

void PlayerSegment::draw() {
	tilemap[static_cast<int>(floor(xPos))][static_cast<int>(floor(yPos))] = color;
}

//************************************************************************
//************************************************************************


PlayerObject::PlayerObject() {
	xVelocity = 1;
	yVelocity = 0;

	isDead = false;
	gotFood = false;

	spriteColor = BEAUTIFULBLUE;
}

PlayerObject::PlayerObject(uint32 spriteColor) {
	xVelocity = 1;
	yVelocity = 0;

	isDead = false;
	gotFood = false;

	this->spriteColor = spriteColor;
}

PlayerObject::~PlayerObject() {}

void PlayerObject::addSegment() {
	// find last node
	std::shared_ptr<SegmentList> temp = segmentsHead;
	while (temp->next != nullptr) {
		temp = temp->next;
	}

	// initialize data
	std::shared_ptr<SegmentList> newNode = std::make_shared<SegmentList>();
	newNode->next = nullptr;
	newNode->pastXVel = temp->pastXVel;
	newNode->pastYVel = temp->pastYVel;
	newNode->segment = std::make_unique<PlayerSegment>
			(temp->segment->getX() - temp->pastXVel,
			 temp->segment->getY() - temp->pastYVel,
			 BEAUTIFULBLUE);

	// append to end of list
	temp->next = newNode;
}

void PlayerObject::checkCollision(int xPos, int yPos, uint32 snakeColor) {
	if (xPos >= tilemapSizeX || xPos < 0) {
		isDead = true;
	}
	else if (yPos >= tilemapSizeY || yPos < 0) {
		isDead = true;
	}
	else if (tilemap[xPos][yPos] == snakeColor) {
		isDead = true;
	}
	/*else if (tilemap[xPos][yPos] == FOODCOLOR) {
		gotFood = true;
	} */
}

void PlayerObject::init() {
	segmentsHead = std::make_shared<SegmentList>();
	segmentsHead->pastXVel = xVelocity;
	segmentsHead->pastYVel = yVelocity;

	int halfY;
	if (tilemapSizeY % 2 == 0) halfY = tilemapSizeY / 2;
	else					   halfY = (tilemapSizeY / 2) + 1;

	segmentsHead->segment = std::make_unique<PlayerSegment>(5.0f, static_cast<int>(halfY), BEAUTIFULBLUE);
}

void PlayerObject::update() {
	// Set collisions to false
	gotFood = false;
	isDead = false;

	int tempX_1 = segmentsHead->pastXVel;
	int tempY_1 = segmentsHead->pastYVel;

	std::shared_ptr<SegmentList> temp = segmentsHead;

	if (runNumber % static_cast<int>( 1.0f / velocityScaleX) == 0) {
		segmentsHead->pastXVel = xVelocity;
		segmentsHead->pastYVel = yVelocity;

		// Check collision in new position
		checkCollision(static_cast<int>(floor(temp->segment->getX() + temp->pastXVel)),
			           static_cast<int>(floor(temp->segment->getY() + temp->pastYVel)),
			           temp->segment->getColor());
	}
	
	temp->segment->update(temp->pastXVel, temp->pastYVel);
	temp = temp->next;
	
	while (temp != nullptr) {
		int tempX_2 = temp->pastXVel;
		int tempY_2 = temp->pastYVel;

		if (runNumber % static_cast<int>(1.0f / velocityScaleX) == 0) {
			temp->pastXVel = tempX_1;
			temp->pastYVel = tempY_1;
		}

		
		temp->segment->update(temp->pastXVel, temp->pastYVel);
		

		temp = temp->next;

		tempX_1 = tempX_2;
		tempY_1 = tempY_2;
	}
	
}

void PlayerObject::draw() {
	std::shared_ptr<SegmentList> temp = segmentsHead;
	while (temp->next != nullptr) {
		temp->segment->draw();
		temp = temp->next;
	}

	/*
	// Remove the last node's position
	int xArg = static_cast<int>(floor(temp->segment->getX()) - (temp->pastXVel * velocityScaleX));
	int yArg = static_cast<int>(floor(temp->segment->getY()) - (temp->pastYVel * velocityScaleY));
	tilemap[xArg][yArg] = calculateTileColor(xArg, yArg);

	*/
}