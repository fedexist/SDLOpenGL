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
	int reaction_counter = 0;
	int reaction = 10;
	Player* enemy;
public:
	void update(float distance, float dt,std::vector<GLint*> logicLevelMap, std::vector<GLint*> objectLevelMap, GLint H, GLint W);
	Player* myCharacter;
	AI(Player* myCharacter, Player* enemy);
	AI(){};
	~AI();
};

