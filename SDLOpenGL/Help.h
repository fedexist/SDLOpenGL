#pragma once
#include "Button.h"
#include "Text.h"
#include "FontManager.h"

class Help
{
	friend class GameClass;
	friend class Button;
	std::vector<Button*> buttons;
	std::vector<Text*> texts;
	Background* background;
	LWindow* window;
	glm::vec2 dimButton;
	glm::vec2 dimBackground;

public:
	Help(LWindow*, FontManager*);
	~Help();
	void render();
	int selectedButton;
	void selectedCheck();
	float centredCoor(float dimPlane, float dimObj);
	void onUpdateWindow();
	glm::vec2 relativeCoor2pxCoor(glm::vec2 relCoor, glm::vec2 dimensions);
};

