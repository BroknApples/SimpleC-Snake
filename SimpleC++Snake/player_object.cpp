#include "player_object.h"

PlayerSegment::PlayerSegment(int xPos, int yPos, uint32 color) {
	this->xPos = xPos;
	this->yPos = yPos;
	this->color = color;
}

void PlayerSegment::update(int xVel, int yVel) {
	// update position
	xPos += (xVel * velocityScaleX);
	xPos = clamp(0, xPos, tilemapSizeX - 1);
	yPos += (yVel * velocityScaleY);
	yPos = clamp(0, yPos, tilemapSizeY - 1);


	// could take a linked list or some other storage type 
	// and pass down the position 1 step further into the list, as long as it is not nullptr
	// rather than trying to figure out ow the position should change for each and every one.
}

void PlayerSegment::draw() {
	tilemap[xPos][yPos] = color;
}

//************************************************************************
//************************************************************************


PlayerObject::PlayerObject() {
	xVelocity = 1;
	yVelocity = 0;

	spriteColor = BEAUTIFULBLUE;
}

PlayerObject::PlayerObject(uint32 spriteColor) {
	xVelocity = 1;
	yVelocity = 0;

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
		(temp->segment->getX(), temp->segment->getY(), BEAUTIFULBLUE);

	// append to end of list
	temp->next = newNode;
}


void PlayerObject::init() {
	segmentsHead = std::make_shared<SegmentList>();
	segmentsHead->pastXVel = xVelocity;
	segmentsHead->pastYVel = yVelocity;

	int halfY;
	if (tilemapSizeY % 2 == 0) halfY = tilemapSizeY / 2;
	else					   halfY = (tilemapSizeY / 2) + 1;

	segmentsHead->segment = std::make_unique<PlayerSegment>(1, halfY, BEAUTIFULBLUE);
}

void PlayerObject::update() {
	int tempX = segmentsHead->pastXVel;
	int tempY = segmentsHead->pastYVel;

	segmentsHead->pastXVel = xVelocity;
	segmentsHead->pastYVel = yVelocity;

	std::shared_ptr<SegmentList> temp = segmentsHead;
	while (temp != nullptr) {
		temp->segment->update(temp->pastXVel, temp->pastYVel);
		temp = temp->next;
	}
}

void PlayerObject::draw() {
	std::shared_ptr<SegmentList> temp = segmentsHead;
	while (temp != nullptr) {
		temp->segment->draw();

		// remove last node's position
		if (temp->next == nullptr) {
			tilemap[(temp->segment->getX() - (temp->pastXVel * velocityScaleX))]
				   [(temp->segment->getY() - (temp->pastYVel * velocityScaleY))]
				   = calculateTileColor((temp->segment->getX() - (temp->pastXVel * velocityScaleX)),
										(temp->segment->getY() - (temp->pastYVel * velocityScaleY)));
		}

		temp = temp->next;

		// tilemap[x - (xVelocity * velocityScaleX)][y - (yVelocity * velocityScaleY)]
		//	= calculateTileColor((x + (xVelocity * velocityScaleX)), (y + (yVelocity * velocityScaleY)));
	}
}