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

void Player::Move(Direction d)
{
	currentState = MOVING;
	if( currentDirection != d)
	{
		currentDirection = d;
		switch(currentDirection)
		{
		case LEFT: 
			curIndexFrame = startingIndexFrame = movingLeftStart;
			endingIndexFrame = movingLeftStart + numberOfMovingFrames - 1;
			break;
		case RIGHT:
			curIndexFrame = startingIndexFrame = movingRightStart;
			endingIndexFrame = movingRightStart + numberOfMovingFrames - 1;
			break;
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

	}
}

void Player::Slash(Direction d)
{
	 
	currentState = SLASHING;
	if( currentDirection != d)
	{
		currentDirection = d;
		switch(currentDirection)
		{
			case LEFT: 
				curIndexFrame = startingIndexFrame = slashingLeftStart;
				endingIndexFrame = slashingLeftStart + numberOfSlashingFrames - 1;
				break;
			case RIGHT:
				curIndexFrame = startingIndexFrame = slashingRightStart;
				endingIndexFrame = slashingRightStart + numberOfSlashingFrames - 1;
				break;
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

	}

}

void Player::Idle()
{
	currentState = IDLE;
	switch (currentDirection)
	{
	case LEFT:
		curIndexFrame = startingIndexFrame = movingLeftStart;
		endingIndexFrame = movingLeftStart + numberOfIdleFrames - 1;
		break;
	case RIGHT:
		curIndexFrame = startingIndexFrame = movingRightStart;
		endingIndexFrame = movingRightStart + numberOfIdleFrames - 1;
		break;
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
}
