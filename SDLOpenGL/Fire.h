#pragma once
#include "GameObject.h"
class Fire :
	public GameObject
{
public:
	Fire(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, LTexture2D* tex, float mass, unsigned int begInd, unsigned int endInd);
	Fire(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, float mass, Fire* other);
	void update(float dt);
	~Fire();
private:
	void onInteraction();
};

