#include "stdafx.h"
#include "Launcher.h"
#include "Button.h"


Launcher::Launcher()
{
	buttons = std::vector<Button*>();
	buttons.push_back(new Button(glm::vec2(0.55, 1.5), glm::vec2(300, 200), new LTexture2D("./assets/button.png", 300, 200), GAME));
	buttons.push_back(new Button(glm::vec2(0.55, 1), glm::vec2(300, 200), new LTexture2D("./assets/button.png", 300, 200), CREDITS));
	backgroundPath = "";

	selectedCheck();
}

void Launcher::render()
{
	for (Button* button : buttons)
	{
		button->render();
	}
	

}

Launcher::~Launcher()
{
}

void Launcher::selectedCheck()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		if (i == selectedButton)
		{
			buttons.at(i)->setCurSprite(BUTTON_SPRITE_OVER_MOTION);
		}
		else
		{
			buttons.at(i)->setCurSprite(BUTTON_SPRITE_OUT);
		}
	}
}
