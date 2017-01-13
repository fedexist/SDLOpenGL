#pragma once
#include "GameObject.h"

class Chest :
	public GameObject
{

public:
		enum Treasure { KEY,COIN };
	Chest(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, LTexture2D* tex, float mass, unsigned int begInd, unsigned int endInd, AudioManager *am);
	Chest(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, float mass, Chest* other);
	void addTreasure(Treasure);
	void update(float dt);
	~Chest();
private:
	Treasure treasure;
	void onInteraction();
	bool open = false;
};

