#pragma once
#include "GameObject.h"

class Door :
	public GameObject
{

public:
		
	Door(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, LTexture2D* tex, float mass, unsigned int begInd, unsigned int endInd, AudioManager *am);
	Door(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, float mass, Door* other);
	void update(float dt);
	~Door();
private:
	void onInteraction();
	bool open = false;
};

