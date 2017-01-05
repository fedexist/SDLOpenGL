#include "stdafx.h"
#include "AI.h"



AI::AI(Player* myCharacter, Player* enemy)
{
	this->myCharacter = myCharacter;
	this->enemy = enemy;
	curState = idle;
}

void AI::update(float distance, float dt)
{
	changeState(distance);
	//dothings
	pathfinder_.updateWorld();
	switch (curState)
	{
		
		case seek:
		{
			if (reaction < 10)
			{
				reaction++;
			}
			else
			{
				reaction = 0;
				//A*;
				currentPath.clear();
				currentPath = pathfinder_.findPath(myCharacter->currentCell(), enemy->currentCell()); //calcolo del nuovo percorso
				pathIterator = currentPath.begin(); //nuovo iteratore impostato
				nextNode = *pathIterator; //primo nodo obiettivo
			}  
			if(myCharacter->currentCell() == nextNode.first)
			{
				nextNode = *(++pathIterator);
				
			}
			myCharacter->Act(MOVING, nextNode.second);			
			break;		
		}
		case destroy:
		{
			myCharacter->Act(SLASHING,glm::vec2(0,1));
			break;
		}
		default: break;
	}
	//SDL_LogDebug(0,"%d", curState);
	myCharacter->update(dt);
}

bool AI::changeState(float distance)
{
	float k_seek = 5;
	float k_destroy = 0.33;
	float k_idle = 7;

	if (enemy->lifepoints < 0.1)
	{
		curState = idle;
		return true;
	}

	if (curState == idle)
	{
		if (distance < k_seek)
		{
			curState = seek;
			return true;
		}
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
		else if (myCharacter->lifepoints < 0.1)
		{
			curState = ripinpepperoni;
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
