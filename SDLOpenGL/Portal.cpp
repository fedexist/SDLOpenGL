#include "stdafx.h"
#include "Portal.h"


Portal::Portal(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, LTexture2D* tex, float mass, unsigned int begInd, unsigned int endInd, AudioManager* am) :
GameObject(pos, mom, dim, vis, canInt, tex, mass, begInd, endInd, am)
{
}

Portal::Portal(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, float mass, Portal* other) :
GameObject(pos, mom, dim, vis, canInt, other->tex, mass, other->startingIndexFrame, other->endingIndexFrame, other->audio_manager)
{
}


void Portal::onInteraction()
{
	return;
	if (open)
		return;

	for (int i = 0; i < areaSharing.size(); i++)
	{
		if (areaSharing.at(i)->isPlayer)
		{
			open = true;
			curIndexFrame = startingIndexFrame = 1;
			endingIndexFrame = 2;
			audio_manager->playSoundEffect("OpenPortal");
			Player* player = dynamic_cast<Player*> (areaSharing.at(i));
			//player->treasureAnimate(treasure);
		}
	}
}

void Portal::update(float dt)
{
	onInteraction();
	handleAnims(dt);
	glm::vec2 forceInput = glm::vec2(0.f, 0.f);

	//movement
	handleMovement(dt, forceInput);

}

Portal::~Portal()
{
}
