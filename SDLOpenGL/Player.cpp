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
	
	if (currentState == MOVING)
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

void Player::Move(glm::vec2 d)
{

	if( currentDirection != d || currentState == IDLE)
	{	
		currentState = MOVING;
		currentDirection = d;
		Direction uD, lR;
		
		uD = static_cast<Direction>(static_cast<int>(currentDirection.y));
		lR = static_cast<Direction>(static_cast<int>(currentDirection.x));
		
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

void Player::Slash(glm::vec2 d)
{
	 
	currentState = SLASHING;
	if( currentDirection != d)
	{
		currentDirection = d;
		Direction uD, lR;

		uD = static_cast<Direction>(static_cast<int>(currentDirection.y));
		lR = static_cast<Direction>(static_cast<int>(currentDirection.x));

		switch (uD)
		{
		case UP:
			curIndexFrame = startingIndexFrame = slashingUpStart;
			endingIndexFrame = slashingUpStart + numberOfSlashingFrames - 1;
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
			curIndexFrame = startingIndexFrame = slashingLeftStart;
			endingIndexFrame = slashingLeftStart + numberOfSlashingFrames - 1;
			break;
		case RIGHT:
			curIndexFrame = startingIndexFrame = slashingDownStart;
			endingIndexFrame = slashingDownStart + numberOfSlashingFrames - 1;
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
