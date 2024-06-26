#ifndef SCORE_OBJECT_H
#define SCORE_OBJECT_H

#include "object_manager.h"

class ScoreObject : public WorldObject {

private:
	int score;

public:
	
	inline void init() override {
		score = 0;
		id = getNewObjectID();
	}

	inline void addScore() { score++; }
	inline const int getScore() { return score; }

	template <typename... TArgs> inline void setScore(TArgs... mArgs) {
		score = 0;
		for (auto& arg : { mArgs... }) {
			score += arg;
		}
	}
};

#endif