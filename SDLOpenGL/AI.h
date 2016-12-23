#pragma once
class AI
{
	enum FSMstate { idle, seek, destroy, ripinpepperoni };
	FSMstate curState;
	bool changeState();
public:
	void update(float dt);
	Player* myCharacter;
	AI(Player* myCharacter);
	~AI();
};

