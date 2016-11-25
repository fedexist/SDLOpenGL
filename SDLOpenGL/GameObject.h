#pragma once
#include "LTexture2D.h"

class GameObject{

	friend class GameClass;

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

protected:
	unsigned int curIndexFrame;
	unsigned int startingIndexFrame;
	unsigned int endingIndexFrame;
	unsigned int framePeriodIndex;
	bool isPlayer = false;
	void handleMovement(float dt, glm::vec2 forceInput);
	void handleAnims(float dt);

};

