#include "stdafx.h"
#include "AI.h"

PathFinder AI::pathfinder_ = PathFinder();

AI::AI(Player* myCharacter, Player* enemy)
{
	this->myCharacter = myCharacter;
	this->enemy = enemy;
	curState = idle;
}

void AI::update(float distance, float dt, std::vector<GLint*> logicLevelMap, std::vector<GLint*> objectLevelMap, GLint H, GLint W)
{
	if(changeState(distance))
	//SDL_LogDebug(0, "State has changed");
	//dothings
	pathfinder_.updateWorld(logicLevelMap, objectLevelMap, H,W);
	switch (curState)
	{
		
		case seek:
		{
			if (SDL_GetTicks() - reaction_counter < reaction)
			{
				//tempo passa
			}
			else
			{
				reaction_counter = SDL_GetTicks();
				//A*;
				currentPath.clear();
				currentPath = pathfinder_.findPath(myCharacter->currentCell(), enemy->currentCell()); //calcolo del nuovo percorso
				pathIterator = currentPath.begin(); //nuovo iteratore impostato
				if(currentPath.size() == 1)
					nextNode = *pathIterator; //primo nodo obiettivo se c'è un solo passo necessario
				else
					nextNode = *++pathIterator; //primo nodo obiettivo se c'è più di un passo
			}  
			if(myCharacter->isHitboxInsideCell(nextNode.first) && *(pathIterator + 1) != currentPath.back() && currentPath.size() > 1)
			{
				SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Going to nextNode");
				nextNode = *(++pathIterator);
				SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Objective node is: %f, %f", nextNode.first.x, nextNode.first.y);
				SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Objective direction is: %f, %f", nextNode.second.x, nextNode.second.y);
				
			}
			if(currentPath.size() > 1)
			{
				myCharacter->Act(MOVING, nextNode.second);	
			}
			/*
			if (!myCharacter->isHitboxInsideCell(nextNode.first))
			{
				//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "direction: %f %f", nextNode.second.x, nextNode.second.y);
				//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "FSMState: %d, AnimationState: %d", curState, myCharacter->currentState);
				

			}*/
			break;
		}
		case destroy:
		{
			unsigned int hitDirectionX;
			unsigned int hitDirectionY;

			if (enemy->spriteCenter().x < myCharacter->spriteCenter().x)
				hitDirectionX = LEFT;
			else
				hitDirectionX = RIGHT;

			if (enemy->spriteCenter().y < myCharacter->spriteCenter().y)
				hitDirectionY = DOWN;
			else
				hitDirectionY = UP;
			
			if (int (SDL_GetTicks() - myCharacter->coolDown) > 0 )
			{
				myCharacter->Act(SLASHING, glm::vec2(hitDirectionY, hitDirectionX));
				myCharacter->coolDown = SDL_GetTicks() + 500;
			}
			
			break;
		}
		case idle:
		{
			myCharacter->Act(IDLE, myCharacter->currentDirection);
		}
		default: break;
	}
	//SDL_LogDebug(0,"%d", curState);
	myCharacter->update(dt);
}

bool AI::changeState(float distance)
{
	float k_seek = 15;
	float k_destroy = 0.33;
	float k_idle = 30;

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
			SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "FSM is Going idle");
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
