#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "utilities.h"

static int objectID = 0;

inline int getNewObjectID() {
	return objectID++;
}

struct WorldObject {
	uint32 id = NULL;

	virtual void init() {}

	virtual void update() {}
	virtual void draw() {}

	inline int getObjectID() const { return id; }

	void updatePosition() {

	}
	void checkCollision() {

	}
};

#include "player_object.h"
#include "score_object.h"

class ObjectManager {

private:
	std::vector<std::shared_ptr<WorldObject>> objects;

public:

	template <typename T, typename... TArgs> T& addObject(TArgs&&... mArgs) {
		T* obj = new T(mArgs...);

		std::shared_ptr<T> ptr{ obj };
		objects.emplace_back(std::move(ptr));

		obj->init();

		return *obj;
	}

	void removeObject(int id) {
		objects.erase(objects.begin() + id);
	}

	inline void update() {
		for (auto& obj : objects) {
			obj->update();
		}
	}
	
	inline void draw() {
		for (auto& obj : objects) {
			obj->draw();
		}
	}
};
#endif