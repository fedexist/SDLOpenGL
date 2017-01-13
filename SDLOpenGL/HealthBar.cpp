#include "stdafx.h"
#include "HealthBar.h"


HealthBar::HealthBar(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, LTexture2D* tex, float mass, unsigned int begInd, unsigned int endInd) :
GameObject(pos, mom, dim, vis, canInt, tex, mass, begInd, endInd,NULL)
{
	level = 8;
}

HealthBar::HealthBar(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, float mass, HealthBar* other) :
GameObject(pos, mom, dim, vis, canInt, other->tex, mass, other->startingIndexFrame, other->endingIndexFrame,NULL)
{
	level = 8;
}

void HealthBar::healthToLevel(float life)
{
	level = 8 - floor(8 * (1000 - life) / 1000); //Full life: 8 - (ceil(8*0/1000)) = 8 / half life : 8 - (ceil(8*500/1000)) = 4 / no life: 8 - (ceil(8*1000/1000)) = 0
	//SDL_LogDebug(0, "health level %d, life%f", level, life);
	int index = (8 - level)*8;
	curIndexFrame = startingIndexFrame = index;
	endingIndexFrame = startingIndexFrame+1;

}

void HealthBar::update(float dt)
{
	//SDL_LogDebug(0, "%f %d", timer, SDL_GetTicks());
	
	if (startingIndexFrame == 9 && timer - SDL_GetTicks() < 1750)
	{
		curIndexFrame = startingIndexFrame = 12;
		endingIndexFrame = 13; //blocca animazione della chiave
	}

	if (timer-SDL_GetTicks() < 0)
	{
		int index = (8 - level)*8;
		curIndexFrame = startingIndexFrame = index;
		endingIndexFrame = startingIndexFrame+1;
	}
	handleAnims(dt);
}

HealthBar::~HealthBar()
{
}
