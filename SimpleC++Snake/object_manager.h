#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "utilities.h"
#include "renderer.h"

class ObjectManager;

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

	virtual void checkCollision(int xPos, int yPos, uint32 color) {}
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

		return *obj;
	}

	void removeObject(int id) {
		objects.erase(objects.begin() + id);
	}

	inline void init() {
		for (auto& obj : objects) {
			obj->init();
		}
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