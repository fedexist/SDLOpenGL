#pragma once
#include "GameObject.h"

typedef enum { MOVING, SLASHING, IDLE, HURT, MOVING_SLASHING } State;
typedef enum { UP, LEFT, DOWN, RIGHT } Direction;

class Player : public GameObject
{
	float lifepoints;
	float damage;
	State currentState = IDLE;
	glm::vec2 currentDirection = glm::vec2(RIGHT,DOWN);	

	//Indici per le animazioni nello spritesheet

	//Idle
	unsigned int numberOfIdleFrames = 2;
	/*
	unsigned int idleUpStart = 52;
	unsigned int idleLeftStart = 65;
	unsigned int idleDownStart = 78;
	unsigned int idleRightStart = 91;*/

	std::array<std::array<unsigned int, 4>, 5> startingIndexMatrix{
		{
			std::array<unsigned int, 4> {{ 104, 117, 130, 143 }}, //Moving
			std::array<unsigned int, 4>{{ 156, 169, 182, 195 }}, //Slashing
			std::array<unsigned int, 4>{{ 104, 117, 130, 143 }}, //Idle
			std::array<unsigned int, 4>{{ 260, 260, 260, 260 }}, //Hurt
			std::array<unsigned int, 4>{{ 156, 169, 182, 195 }} //MovingSlashing

		} };

	std::array<unsigned int, 5> numberOfFrames{ { 9, 6, 2, 6, 6 } };

	//Movimento
	unsigned int numberOfMovingFrames = 9;
	unsigned int movingUpStart = 104;
	unsigned int movingLeftStart = 117;
	unsigned int movingDownStart = 130;
	unsigned int movingRightStart = 143;
	

	//Slash
	unsigned int numberOfSlashingFrames = 6;
	unsigned int slashingUpStart = 156;
	unsigned int slashingLeftStart = 169;
	unsigned int slashingDownStart = 182;
	unsigned int slashingRightStart = 195;

	//Hurt
	unsigned int numberOfHurtFrames = 6;
	unsigned int hurtStart = 260;


public:
	Player(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, LTexture2D* tex, float mass, unsigned int begInd, unsigned int endInd);
	~Player();
	void setCurrentState(State s) { currentState = s; }

	void update(float dt);

	bool isMoving(glm::vec2 d) const { return currentState == MOVING && currentDirection == d; }
	bool isSlashing(glm::vec2 d) const { return currentState == SLASHING && currentDirection == d; }
	bool isIdle(glm::vec2 d) const { return currentState == IDLE && currentDirection == d; }

	void Act(State s, glm::vec2 d);

	void Move(glm::vec2 d);
	void Slash(glm::vec2 d, bool isMoving);
	void Idle();
};

