#pragma once
#include "LTexture2D.h"

class GameObject{
	glm::vec2 position;
	glm::vec2 momentum;
	glm::vec2 dimensions;
	bool visible;
	bool canInteractWith;
	LTexture2D* tex;
	unsigned int curIndexFrame;
	unsigned int startingIndexFrame;
	unsigned int endingIndexFrame;
	unsigned int framePeriodIndex;
	float mass;
public:
	GameObject(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, LTexture2D* tex, float mass, unsigned int begInd, unsigned int endInd);
	~GameObject();
	void render();
	void update(float dt);
};

