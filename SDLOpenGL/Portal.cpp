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
	

	for (int i = 0; i < areaSharing.size(); i++)
	{

		if (areaSharing.at(i)->isPlayer)
		{
			
			if (open)
			{
				UpLeft->teleporting++;
				return;
			}
		
		Player* player = dynamic_cast<Player*> (areaSharing.at(i));
		if (player->num_of_keys > 0)
			{
				player->num_of_keys--;

				audio_manager->ManageMusic(STOP, "MainTheme", MIX_FADING_OUT, 2000);
				audio_manager->playSoundEffect("OpenPortal");
				UpLeft->timeOpening = SDL_GetTicks();
				UpLeft->openPortal();
			}
		}
	}
}

void Portal::openPortal()
{
	open = true;
	startingIndexFrame -= 2;
	curIndexFrame -= 2;
	endingIndexFrame -= 2;
	if (Next)
		Next->openPortal();
}

void Portal::teleport()
{
	for (int i = 0; i < areaSharing.size(); i++)
	{
		if (areaSharing.at(i)->isPlayer)
		{
			Player* thisPlayer = dynamic_cast<Player*>(areaSharing.at(i));
			thisPlayer->myHealthBar->visible = false;
			thisPlayer->visible = false;
		}
		return;
	}
	Next->teleport();
}


void Portal::update(float dt)
{
	if (UpLeft == this) {
		teleporting = 0;
	}
	onInteraction();
	
	if (UpLeft->teleporting>=2 && SDL_GetTicks()-UpLeft->timeOpening > 1000) 
		UpLeft->teleport();
	
	//UpLeft->teleport();
	handleAnims(dt);
	glm::vec2 forceInput = glm::vec2(0.f, 0.f);

	//movement
	handleMovement(dt, forceInput);

}

Portal::~Portal()
{
}
