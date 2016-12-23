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
	float distance = 0;
	float k_seek = 0;
	float k_destroy = 0;
	float k_idle = 0;
	if (curState == idle)
	{
		if (distance < k_seek)
		{
			curState = seek;
			return true;
		}
		return false;
	}
	else if (curState == seek)
	{
		if (distance < k_destroy)
		{
			curState = destroy;
			return true;
		}
		else if (distance > k_seek)
		{
			curState = idle;
			return true;
		}
	}
	else if (curState == destroy)
	{
		if (distance > k_destroy)
		{
			curState = seek;
			return true;
		}
		else if (myCharacter->lifepoints < 0.1)
		{
			curState = ripinpepperoni;
			return true;
		}
	}
	return false;
}



AI::~AI()
{
}
