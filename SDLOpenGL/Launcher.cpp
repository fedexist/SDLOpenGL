#include "stdafx.h"
#include "Launcher.h"
#include "Button.h"

Launcher::Launcher()
{
	buttons = std::vector<Button*>();
	glm::vec2 dimButton = glm::vec2(256, 64);
	glm::vec2 dimDrawPlane = glm::vec2(640, 640);
	
	buttons.push_back(new Button(glm::vec2(centredCoor(dimDrawPlane.x, dimButton.x), centredCoor(dimDrawPlane.y,dimButton.y)-3), dimButton, new LTexture2D("./assets/button_start.png", dimButton.x, dimButton.y), GAME));
	//buttons.push_back(new Button(glm::vec2(centredCoor(dimDrawPlane.x, dimButton.x)+0.5, centredCoor(dimDrawPlane.y, dimButton.y)-3), dimButton, new LTexture2D("./assets/button_credits.png", dimButton.x, dimButton.y), CREDITS));
	background = new LTexture2D("./assets/background_launcher.png", 640, 640);
	title = new LTexture2D("./assets/title.png",512, 128);

	selectedCheck();
}

void Launcher::render()
{
	background->drawSprite(0, 0, -1, 0);
	for (Button* button : buttons)
	{
		button->render();
	}
	
	title->drawSprite(centredCoor(640, 512), centredCoor(640, 128) + 1.75, 0, 0);
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

float Launcher::centredCoor(float dimPlane, float dimObj)
{
	float result = (dimPlane / dimObj) / 2 - (dimObj / dimObj) / 2;
	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "result: %f", result);
	return result;
}
