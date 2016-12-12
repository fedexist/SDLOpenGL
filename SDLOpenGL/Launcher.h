#pragma once
#include "Button.h"

class Launcher
{
	friend class GameClass;
	std::vector<Button*> buttons;
	LTexture2D* background;
	LTexture2D* title;
	

public:
	Launcher();
	~Launcher();
	void render();
	int selectedButton = -1;
	void selectedCheck();
	float centredCoor(float dimPlane, float dimObj);
};

