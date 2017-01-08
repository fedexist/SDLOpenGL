#pragma once
#include "PathFinder.h"

class AI
{
	enum FSMstate { idle, seek, destroy, ripinpepperoni };
	FSMstate curState;

	static PathFinder pathfinder_;
	NodeDirection nextNode; //attuale nodo verso il quale ci stiamo muovendo
	std::vector< NodeDirection > currentPath; //l'ultimo array calcolato da findPath
	std::vector< NodeDirection >::iterator pathIterator; //iteratore per scorrere il vettore
	
	bool changeState(float distance);
	unsigned int reaction_counter = 10;
	int reaction = reaction_counter;
	unsigned int movement_cooldown = 0;
	Player* enemy;
public:
	void update(float distance, float dt,std::vector<GLint*> logicLevelMap, std::vector<GLint*> objectLevelMap, GLint H, GLint W);
	Player* myCharacter;
	AI(Player* myCharacter, Player* enemy);
	AI(){};
	~AI();
};

