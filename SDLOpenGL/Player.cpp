#include "stdafx.h"
#include "Player.h"


Player::Player(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, LTexture2D* tex, float mass, unsigned int begInd, unsigned int endInd): 
	GameObject(pos, mom, dim, vis, canInt, tex, mass, begInd, endInd)
{
	lifepoints = 1000.0f;
	damage = 50.0f;
	isPlayer = true;
}


Player::~Player()
{
}

void Player::update(float dt)
{

	handleAnims(dt);
	glm::vec2 forceInput = glm::vec2(0.0f,0.0f);
	
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
	}
	
	//SDL_LogDebug(0, "%f %f", forceInput.x, forceInput.y);

	//movement
	handleMovement(dt, forceInput);

}

void Player::Act(State s, glm::vec2 d)
{

	if(s == SLASHING)
	{
		unsigned int direction = -1;
		unsigned int uD, lR;
		
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
		tex->framePeriod = 10;

		if(startingIndexFrame != startingIndexMatrix[s][direction] )
		{
			curIndexFrame = startingIndexFrame = startingIndexMatrix[s][direction];
			endingIndexFrame = startingIndexMatrix[s][direction] + numberOfFrames[s] - 1;		
		}

	} else if(currentState == IDLE && s == MOVING || currentState == MOVING && s==MOVING && currentDirection != d)
	{
		int direction = -1;
		unsigned int uD, lR;
		
		uD = static_cast<int>(d.y);
		lR = static_cast<int>(d.x);

		if(uD != -1 || lR != -1)
		{
			direction = uD;
			if (lR != -1)
				direction = lR;
		}
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Actual animation direction: %d", direction);
		currentState = s;
		currentDirection = d;
		tex->framePeriod = 6;

		curIndexFrame = startingIndexFrame = startingIndexMatrix[s][direction];
		endingIndexFrame = startingIndexMatrix[s][direction] + numberOfFrames[s] - 1;
		


	} else if(s == MOVING_SLASHING)
	{
		int direction = -1;
		unsigned int uD, lR;
		
		uD = static_cast<int>(d.y);
		lR = static_cast<int>(d.x);

		if(uD != -1 || lR != -1)
		{
			direction = uD;
			if (lR != -1)
				direction = lR;
		}

		currentState = s;
		tex->framePeriod = 10;
		currentDirection = d;

		if(startingIndexFrame != startingIndexMatrix[s][direction] )
		{
			curIndexFrame = startingIndexFrame = startingIndexMatrix[s][direction];
			endingIndexFrame = startingIndexMatrix[s][direction] + numberOfFrames[s] - 1;		
		}
	} else if(s==IDLE)
	{
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
		curIndexFrame = startingIndexFrame = startingIndexMatrix[s][direction];
		endingIndexFrame = startingIndexMatrix[s][direction] + numberOfFrames[s] - 1;		
	
	}
}

/*
void Player::Move(glm::vec2 d)
{

	if( currentDirection != d || currentState == IDLE)
	{	
		currentState = MOVING;
		currentDirection = d;
		Direction uD, lR;
		
		uD = static_cast<Direction>(static_cast<int>(currentDirection.y));
		lR = static_cast<Direction>(static_cast<int>(currentDirection.x));
		
		tex->framePeriod = 5;

		switch(uD)
		{
		case UP:
			curIndexFrame = startingIndexFrame = movingUpStart;
			endingIndexFrame = movingUpStart + numberOfMovingFrames - 1;
			break;	
		case DOWN:
			curIndexFrame = startingIndexFrame = movingDownStart;
			endingIndexFrame = movingDownStart + numberOfMovingFrames - 1;
			break;
		default: break;
		}
		switch (lR)
		{
		case LEFT:
			curIndexFrame = startingIndexFrame = movingLeftStart;
			endingIndexFrame = movingLeftStart + numberOfMovingFrames - 1;
			break;
		case RIGHT:
			curIndexFrame = startingIndexFrame = movingRightStart;
			endingIndexFrame = movingRightStart + numberOfMovingFrames - 1;
			break;
		default: break;
		}
	}
}

void Player::Slash(glm::vec2 d, bool isMoving)
{
	if( currentDirection != d)
	{
		currentState = SLASHING;
		currentDirection = d;
		Direction uD, lR;

		uD = static_cast<Direction>(static_cast<int>(currentDirection.y));
		lR = static_cast<Direction>(static_cast<int>(currentDirection.x));

		tex->framePeriod = 10;

		switch (uD)
		{
		case UP:
			curIndexFrame = startingIndexFrame = slashingUpStart;
			endingIndexFrame = slashingUpStart + numberOfSlashingFrames - 1;
			break;
		case DOWN:
			curIndexFrame = startingIndexFrame = slashingDownStart;
			endingIndexFrame = slashingDownStart + numberOfSlashingFrames - 1;
			break;
		default: break;
		}
		switch (lR)
		{
		case LEFT:
			curIndexFrame = startingIndexFrame = slashingLeftStart;
			endingIndexFrame = slashingLeftStart + numberOfSlashingFrames - 1;
			break;
		case RIGHT:
			curIndexFrame = startingIndexFrame = slashingRightStart;
			endingIndexFrame = slashingRightStart + numberOfSlashingFrames - 1;
			break;
		default: break;
		}

	}

}

void Player::Idle()
{
	currentState = IDLE;
	Direction uD, lR;

		uD = static_cast<Direction>(static_cast<int>(currentDirection.y));
		lR = static_cast<Direction>(static_cast<int>(currentDirection.x));

	switch (uD)
	{
	case UP:
		curIndexFrame = startingIndexFrame = movingUpStart;
		endingIndexFrame = movingUpStart + numberOfIdleFrames - 1;
		break;
	case DOWN:
		curIndexFrame = startingIndexFrame = movingDownStart;
		endingIndexFrame = movingDownStart + numberOfIdleFrames - 1;
		break;
	default: break;
	}
	switch (lR)
	{
	case LEFT:
		curIndexFrame = startingIndexFrame = movingLeftStart;
		endingIndexFrame = movingLeftStart + numberOfIdleFrames - 1;
		break;
	case RIGHT:
		curIndexFrame = startingIndexFrame = movingRightStart;
		endingIndexFrame = movingRightStart + numberOfIdleFrames - 1;
		break;
	default: break;
	}
		
}
*/