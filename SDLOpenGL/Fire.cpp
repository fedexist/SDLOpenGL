#include "stdafx.h"
#include "Fire.h"


Fire::Fire(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, LTexture2D* tex, float mass, unsigned int begInd, unsigned int endInd) :
GameObject(pos, mom, dim, vis, canInt, tex, mass, begInd, endInd, NULL)
{
}

Fire::Fire(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, float mass, Fire* other) :
GameObject(pos, mom, dim, vis, canInt, other->tex, mass, other->startingIndexFrame, other->endingIndexFrame,NULL)
{
}

void Fire::onInteraction()
{
	for (int i = 0; i < areaSharing.size(); i++)
	{
		areaSharing.at(i)->getHit(0.5, this);
	}
}

void Fire::update(float dt)
{
	onInteraction();
	handleAnims(dt);
	glm::vec2 forceInput = glm::vec2(0.f, 0.f);

	//movement
	handleMovement(dt, forceInput);

}

Fire::~Fire()
{
}
