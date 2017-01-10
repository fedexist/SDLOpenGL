#pragma once
#include "GameObject.h"
class HealthBar :
	public GameObject
{
	friend class Player;
	int level;
	
public:
	void healthToLevel(float life);
	void update(float dt);
	HealthBar(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, LTexture2D* tex, float mass, unsigned int begInd, unsigned int endInd);
	HealthBar(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, float mass, HealthBar* other);
	~HealthBar();
};

