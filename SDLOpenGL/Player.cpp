#include "stdafx.h"
#include "Player.h"


Player::Player(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, LTexture2D* tex, float mass, unsigned int begInd, unsigned int endInd): 
	GameObject(pos, mom, dim, vis, canInt, tex, mass, begInd, endInd, nullptr)
{
	lifepoints = 1000.0f;
	damage = 50.0f;
	//isPlayer = true; true only for the player
	Act(IDLE, currentDirection);
}

Player::Player(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, float mass, Player* other) :
GameObject(pos, mom, dim, vis, canInt,other->tex, mass, other->startingIndexFrame,other->endingIndexFrame, nullptr)
{
	lifepoints = 1000.0f;
	damage = 50.0f;
	//isPlayer = true; true only for the player
	Act(IDLE, currentDirection);
}


Player::~Player()
{
}

void Player::getHit(float hitNumber, GameObject* hitter)
{
	
	lifepoints -= hitNumber;
	if (lifepoints <= 0.0f)
	{
		lifepoints = 0.0f;
		Act(HURT, glm::vec2(0, 0));
	}
		

	std::string msg;
	if (this->isPlayer)
		msg = "Player lost %f life thanks to";
	else
		msg = "Monster lost %f life thanks to";

	if (hitter->isPlayer)
		msg += " the Player";
	else 
		msg += " the fire";

	myHealthBar->healthToLevel(lifepoints);
	//SDL_LogDebug(0,msg.c_str(), hitNumber);
}

void Player::update(float dt)
{
	//Gestisco l'animazione normale, cio� periodica
	if (currentState != HURT || (curIndexFrame != hurtStart + numberOfHurtFrames - 2 && currentState == HURT && framePeriodIndex == 1))
		handleAnims(dt);
	else // se sono al penultimo frame dell'animazione di morte e alla fine del suo periodo, passo direttamente al frame finale (altrimenti, l'animazione comincerebbe da capo)
	{	
		curIndexFrame = hurtStart + numberOfHurtFrames - 1;
	}
		

	glm::vec2 forceInput = glm::vec2(0.0f,0.0f);

	if(lifepoints <= 0.0f)
		Act(HURT, glm::vec2(0, 0));

	//SDL_LogDebug(0, "%d", inSlashingAnim());

	if (inSlashingAnim() < -1 && lifepoints > 0.0f)
	{
		Act(IDLE, currentDirection);
	}
	else if (inSlashingAnim() > -1)
	{
		if (inDamagingAnim())
			handleFight();
	}

	if (currentState == MOVING || currentState == MOVING_SLASHING)
	{
		if (currentDirection.x == LEFT)
			forceInput.x = -1.0f;
		else if (currentDirection.x == RIGHT)
			forceInput.x = 1.0f;

		if (currentDirection.y == DOWN)
			forceInput.y = -1.0f;
		else if (currentDirection.y == UP)
			forceInput.y = 1.0f;

		//currentState = MOVING;
	}
	
	//SDL_LogDebug(0, "%f %f", forceInput.x, forceInput.y);

	//movement
	handleMovement(dt, forceInput);

	myHealthBar->position.x = position.x;

	myHealthBar->position.y = position.y + 0.8;

}

void Player::Act(State s, glm::vec2 d, glm::vec2 d2)
{

	if (currentState == HURT)
		return;
	
	if(s == SLASHING)
	{
		unsigned int direction = -1;
		unsigned int uD, lR;
		
		uD = static_cast<int>(d.y);
		lR = static_cast<int>(d.x);

		//SDL_LogDebug(0,"uD %d, lR %d",uD,lR);

		if(uD != -1 || lR != -1)
		{
			direction = uD;
			if (lR != -1)
				direction = lR;
		}

		//SDL_LogDebug(0,"direction %d",direction);

		currentState = s;
		currentDirection = d;
		tex->framePeriod = 40;
		

		if (inSlashingAnim()>-1)
		{
			return;
		}

		curIndexFrame = startingIndexFrame = startingIndexMatrix[s][direction];
		endingIndexFrame = startingIndexMatrix[s][direction] + numberOfFrames[s] - 1;		
		
	}
	else if (currentState == IDLE && s == MOVING || currentState == MOVING && s == MOVING && currentDirection != d || currentState == MOVING_SLASHING && s == MOVING)
	{
		int direction = -1;
		unsigned int uD, lR;
		
		//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Moving");

		uD = static_cast<int>(d.y);
		lR = static_cast<int>(d.x);

		if(uD != -1 || lR != -1)
		{
			direction = uD;
			if (lR != -1)
				direction = lR;
		}
		currentState = s;
		currentDirection = d;
		tex->framePeriod = 60;

		if (inSlashingAnim()>-1)
			return;

		curIndexFrame = startingIndexFrame = startingIndexMatrix[s][direction];
		endingIndexFrame = startingIndexMatrix[s][direction] + numberOfFrames[s] - 1;
		


	} else if(s == MOVING_SLASHING)
	{
		int direction = -1;
		int directionHit = -1;
		unsigned int uD, lR;
		unsigned int uDHit, lRHit;
		
		uD = static_cast<int>(d.y);
		lR = static_cast<int>(d.x);

		uDHit = static_cast<int>(d2.y);
		lRHit = static_cast<int>(d2.x);

		if(uD != -1 || lR != -1)
		{
			direction = uD;
			if (lR != -1)
				direction = lR;
		}

		if (uDHit != -1 || lRHit != -1)
		{
			directionHit = uDHit;
			if (lRHit != -1)
				directionHit = lRHit;
		}

		currentState = s;
		tex->framePeriod = 60;
		currentDirection = d;

		if (inSlashingAnim()>-1)
			return;

		curIndexFrame = startingIndexFrame = startingIndexMatrix[s][directionHit];
		endingIndexFrame = startingIndexMatrix[s][directionHit] + numberOfFrames[s] - 1;		

	} else if(s == HURT && currentState != HURT)
	{

		int direction = 0;
		currentState = s;
		curIndexFrame = startingIndexFrame = startingIndexMatrix[s][direction];
		endingIndexFrame = startingIndexMatrix[s][direction] + numberOfFrames[s] - 1;

	} else if(s==IDLE)
	{

		//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Going Idle" );

		int direction = -1;
		unsigned int uD, lR;
		
		uD = static_cast<int>(currentDirection.y);
		lR = static_cast<int>(currentDirection.x);

		if(uD != -1 || lR != -1)
		{
			direction = uD;
			if (lR != -1)
				direction = lR;
		}

		currentState = s;

		
		if (inSlashingAnim() > -1)
		{
			return;
		}
		
		curIndexFrame = startingIndexFrame = startingIndexMatrix[s][direction];
		endingIndexFrame = startingIndexMatrix[s][direction] + numberOfFrames[s] - 1;		
	
	}
}

void Player::handleFight()
{
	
	for (int i = 0; i < areaSharing.size(); i++)
	{
		areaSharing.at(i)->getHit(10, this);
	}

	//SDL_LogDebug(0, "Fighting direction %d, %d, indexFrrame %d", int(currentDirection.x), int(currentDirection.y), curIndexFrame);
}

void Player::treasureAnimate(int treasure)
{
	
	if (treasure == 1)//coin
	{
		myHealthBar->timer = SDL_GetTicks() + 2000;
		myHealthBar->curIndexFrame = myHealthBar->startingIndexFrame = 1;
		myHealthBar->endingIndexFrame = 8;
	}
	
	if (treasure == 0) //key
	{
		myHealthBar->timer = SDL_GetTicks() + 2000;
		myHealthBar->curIndexFrame = myHealthBar->startingIndexFrame = 9;
		myHealthBar->endingIndexFrame = 13;
		num_of_keys++;
	}
}