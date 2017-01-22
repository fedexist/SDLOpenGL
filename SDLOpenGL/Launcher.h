#pragma once
#include "Button.h"
#include "Background.h"
#include "FontManager.h"
#include "Layout.h"

class Launcher
{
	friend class GameClass;
	std::vector<Button*> buttons;
	std::vector<Text*> texts;
	Background* background;
	LTexture2D* title;
	LWindow* window;
	glm::vec2 dimButton;
	glm::vec2 dimBackground;
	Layout* layout;

public:
	Launcher(LWindow*, FontManager*);
	~Launcher();
	void render();
	int selectedButton;
	void selectedCheck();
	float centredCoor(float dimPlane, float dimObj);
	void onUpdateWindow();
	glm::vec2 relativeCoor2pxCoor(glm::vec2 relCoor, glm::vec2 dimensions);
};

