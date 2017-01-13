#pragma once
#include "GameObject.h"
#include "HealthBar.h"

typedef enum { MOVING, SLASHING, IDLE, HURT, MOVING_SLASHING } State;
typedef enum { UP, LEFT, DOWN, RIGHT } Direction;

class Player : public GameObject
{
	friend class AI;
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

	std::array<std::array<unsigned int, 4>, 5> startingIndexMatrix = std::array<std::array<unsigned int, 4>, 5>{
		{
			std::array<unsigned int, 4> {{ 104, 117, 130, 143 }}, //Moving
			std::array<unsigned int, 4>{{ 156, 169, 182, 195 }}, //Slashing
			std::array<unsigned int, 4>{{ 104, 117, 130, 143 }}, //Idle
			std::array<unsigned int, 4>{{ 260, 260, 260, 260 }}, //Hurt
			std::array<unsigned int, 4>{{ 156, 169, 182, 195 }} //MovingSlashing

		} };

	std::array<unsigned int, 5> numberOfFrames = std::array<unsigned int, 5>{ { 9, 6, 2, 6, 6 } };

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

	void handleFight();

public:
	Player(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, LTexture2D* tex, float mass, unsigned int begInd, unsigned int endInd);
	Player(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, float mass, Player* other);
	~Player();
	unsigned int coolDown = 0;
	void setCurrentState(State s) { currentState = s; }
	
	void update(float dt);
	void getHit(float hitNumber, GameObject* hitter);

	bool isMoving(glm::vec2 d) const { return currentState == MOVING && currentDirection == d; }
	bool isSlashing(glm::vec2 d) const { return currentState == SLASHING && currentDirection == d; }
	bool isIdle(glm::vec2 d) const { return currentState == IDLE && currentDirection == d; }

	void Act(State s, glm::vec2 d, glm::vec2 d2 = glm::vec2(0,0));

	void treasureAnimate(int);

	HealthBar* myHealthBar;

	int inSlashingAnim(){ 
		GLuint upCurIndexFrame = startingIndexMatrix[SLASHING][UP];
		GLuint upEndingIndexFrame = startingIndexMatrix[SLASHING][UP] + numberOfFrames[SLASHING] - 1;

		GLuint dnCurIndexFrame = startingIndexMatrix[SLASHING][DOWN];
		GLuint dnEndingIndexFrame = startingIndexMatrix[SLASHING][DOWN] + numberOfFrames[SLASHING] - 1;

		GLuint lxCurIndexFrame = startingIndexMatrix[SLASHING][LEFT];
		GLuint lxEndingIndexFrame = startingIndexMatrix[SLASHING][LEFT] + numberOfFrames[SLASHING] - 1;

		GLuint rxCurIndexFrame = startingIndexMatrix[SLASHING][RIGHT];
		GLuint rxEndingIndexFrame = startingIndexMatrix[SLASHING][RIGHT] + numberOfFrames[SLASHING] - 1;
		//SDL_LogDebug(0, "%d, uprange %d %d", curIndexFrame, upCurIndexFrame);
		if (curIndexFrame >= upCurIndexFrame && curIndexFrame < upEndingIndexFrame-1)
			return UP;
		if (curIndexFrame >= dnCurIndexFrame && curIndexFrame < dnEndingIndexFrame-1)
			return DOWN;
		if (curIndexFrame >= lxCurIndexFrame && curIndexFrame < lxEndingIndexFrame-1)
			return LEFT;
		if (curIndexFrame >= rxCurIndexFrame && curIndexFrame < rxEndingIndexFrame-1)
			return RIGHT;
		if (curIndexFrame == upEndingIndexFrame-1)
			return UP - 6;
		if (curIndexFrame == dnEndingIndexFrame-1)
			return DOWN - 6;
		if (curIndexFrame == lxEndingIndexFrame-1)
			return LEFT - 6;
		if (curIndexFrame == rxEndingIndexFrame-1)
			return RIGHT - 6;
		return -1;
	};

	bool inDamagingAnim(){
		GLuint upCurIndexFrame = startingIndexMatrix[SLASHING][UP];
		GLuint upEndingIndexFrame = startingIndexMatrix[SLASHING][UP] + numberOfFrames[SLASHING] - 1;

		GLuint dnCurIndexFrame = startingIndexMatrix[SLASHING][DOWN];
		GLuint dnEndingIndexFrame = startingIndexMatrix[SLASHING][DOWN] + numberOfFrames[SLASHING] - 1;

		GLuint lxCurIndexFrame = startingIndexMatrix[SLASHING][LEFT];
		GLuint lxEndingIndexFrame = startingIndexMatrix[SLASHING][LEFT] + numberOfFrames[SLASHING] - 1;

		GLuint rxCurIndexFrame = startingIndexMatrix[SLASHING][RIGHT];
		GLuint rxEndingIndexFrame = startingIndexMatrix[SLASHING][RIGHT] + numberOfFrames[SLASHING] - 1;

		if (curIndexFrame >= upCurIndexFrame && curIndexFrame < upEndingIndexFrame - 3)
			return true;
		if (curIndexFrame >= dnCurIndexFrame && curIndexFrame < dnEndingIndexFrame - 3)
			return true;
		if (curIndexFrame >= lxCurIndexFrame && curIndexFrame < lxEndingIndexFrame - 3)
			return true;
		if (curIndexFrame >= rxCurIndexFrame && curIndexFrame < rxEndingIndexFrame - 3)
			return true;

		return false;

	};

};

