#pragma once
#include "Button.h"
#include "Text.h"
#include "FontManager.h"
#include "Layout.h"

class Help
{
	friend class GameClass;
	std::vector<Button*> buttons;
	std::vector<Text*> texts;
	std::vector<LTexture2D*> images;
	LTexture2D* background_commands;
	Background* background;
	LWindow* window;
	glm::vec2 dimButton;
	glm::vec2 dimBackground;
	Layout* layout;

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

