#pragma once
#include "GameObject.h"

typedef enum { MOVING, SLASHING, IDLE, HURT } State;
typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

class Player :
	public GameObject
{
	float lifepoints;
	float damage;
	State currentState = IDLE;
	Direction currentDirection = DOWN;

	//Indici per le animazioni nello spritesheet

	//Idle
	unsigned int numberOfIdleFrames = 8;
	unsigned int idleUpStart = 52;
	unsigned int idleLeftStart = 65;
	unsigned int idleDownStart = 78;
	unsigned int idleRightStart = 91;

	//Movimento
	unsigned int numberOfMovingFrames = 13;
	unsigned int movingUpStart = 104;
	unsigned int movingLeftStart = 117;
	unsigned int movingDownStart = 130;
	unsigned int movingRightStart = 143;
	

	//Slash
	unsigned int numberOfSlashingFrames = 6;
	unsigned int slashingLeftStart = 156;
	unsigned int slashingRightStart = 169;
	unsigned int slashingUpStart = 182;
	unsigned int slashingDownStart = 195;

	//Hurt
	unsigned int numberOfHurtFrames = 6;
	unsigned int hurtStart = 260;




	

public:
	Player(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, LTexture2D* tex, float mass, unsigned int begInd, unsigned int endInd);
	~Player();
};

