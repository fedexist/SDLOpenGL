#pragma once
#include "LTexture2D.h"

class GameObject{
	friend class GameObjectComparer;
	glm::vec2 position;
	glm::vec2 momentum;
	glm::vec2 dimensions;
	bool visible;
	bool canInteractWith;
	LTexture2D* tex;
	float mass;
public:
	GameObject(glm::vec2 position_, glm::vec2 momentum_, glm::vec2 dimensions_, bool visible_, bool interactable, LTexture2D* texture, float mass, unsigned int beginIndex, unsigned int endingIndex);
	~GameObject();
	void render();
	void update(float dt);
	bool isPlayer = false;
	class GameObjectComparer
	{
		friend class GameObject;
	public:
		GameObjectComparer(){};
		bool operator() (GameObject *i, GameObject *j) {
			return (i->position.y > j->position.y);
		}
	} gameObjectComparer;

protected:
	unsigned int curIndexFrame;
	unsigned int startingIndexFrame;
	unsigned int endingIndexFrame;
	unsigned int framePeriodIndex;
	void handleMovement(float dt, glm::vec2 forceInput);
	void handleAnims(float dt);

};

