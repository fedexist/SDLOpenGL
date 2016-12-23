#include "stdafx.h"
#include "AI.h"


AI::AI(Player* myCharacter)
{
	this->myCharacter = myCharacter;
	curState = idle;
}

void AI::update(float dt)
{
	changeState();
	//dothings
}

bool AI::changeState()
{
	return false;
}


AI::~AI()
{
}
