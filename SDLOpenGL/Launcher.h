#pragma once
#include "Button.h"

class Launcher
{
	friend class GameClass;
	std::string backgroundPath;
	std::vector<Button*> buttons;
	

public:
	Launcher();
	~Launcher();
	void render();
	int selectedButton = 0;
	void selectedCheck();
};

