#include "stdafx.h"
#include "Door.h"


Door::Door(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, LTexture2D* tex, float mass, unsigned int begInd, unsigned int endInd, AudioManager* am) :
GameObject(pos, mom, dim, vis, canInt, tex, mass, begInd, endInd, am)
{
}

Door::Door(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, float mass, Door* other) :
GameObject(pos, mom, dim, vis, canInt, other->tex, mass, other->startingIndexFrame, other->endingIndexFrame, other->audio_manager)
{
}

void Door::onInteraction()
{
	if (open)
		return;

	for (int i = 0; i < areaSharing.size(); i++)
	{
		if (areaSharing.at(i)->isPlayer)
		{
			Player* player = dynamic_cast<Player*> (areaSharing.at(i));
			if (player->num_of_keys>0)
			{	
				open = true;
				player->num_of_keys--;
				audio_manager->playSoundEffect("OpenChest");
			}
			else
			{
				player->Act(MOVING,glm::vec2(-1,UP));
			}
		}
	}
}

void Door::update(float dt)
{
	onInteraction();
	if (open && curIndexFrame < 4)
		handleAnims(dt);
	glm::vec2 forceInput = glm::vec2(0.f, 0.f);

	//movement
	handleMovement(dt, forceInput);

}

Door::~Door()
{
}
