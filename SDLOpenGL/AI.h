#pragma once
class AI
{
	enum FSMstate { idle, seek, destroy, ripinpepperoni };
	FSMstate curState;
	bool changeState(float distance);
	int reaction = 0;
	Player* enemy;
public:
	void update(float distance, float dt);
	Player* myCharacter;
	AI(Player* myCharacter, Player* enemy);
	AI(){};
	~AI();
};

