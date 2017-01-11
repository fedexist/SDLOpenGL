#include "stdafx.h"
#include "Help.h"
#include "Button.h"

//	TODO: [RELEASE] Questa classe non dovrebbe esserci. Tutto ciò è gestibile da un'unica classe Launcher \
	con diversi stati.

Help::Help(LWindow* w)
{
	texts = std::vector<Text*>();
	buttons = std::vector<Button*>();
	dimButton = glm::vec2(256, 64);
	dimBackground = glm::vec2(1024, 640);
	selectedButton = -1;
	window = w;


	SDL_Color color = { 255, 255, 255 };
	background = new Background("./assets/background_launcher.png", 1024, 640);
	buttons.push_back(new Button(glm::vec2(centredCoor(background->getBackgroundDim().x, dimButton.x), 
					centredCoor(background->getBackgroundDim().y, dimButton.y) - 3), 
					dimButton, 
					new LTexture2D("./assets/button_back.png", dimButton.x, dimButton.y), 
					LAUNCHER,
					new Text("./assets/fonts/general_font.ttf", "BACK", color, 50)));

	for (Button* b : buttons)
	{
		b->positionPx = relativeCoor2pxCoor(b->positionRel, dimButton);
	}

	selectedCheck();
}
void Help::render()
{
	background->render();
	for (Button* button : buttons)
	{
		button->render();
	}
	for (Text* text : texts)
	{
		text->drawText(centredCoor(dimBackground.x, text->textDimensions.x), centredCoor(dimBackground.y, text->textDimensions.y));
	}
}

Help::~Help()
{
}

void Help::selectedCheck()
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
		//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "button: %d", selectedButton);
	}
}

float Help::centredCoor(float dimPlane, float dimObj)
{
	float result = (dimPlane / dimObj) / 2 - (dimObj / dimObj) / 2;
	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "result: %f", result);
	return result;
}


glm::vec2 Help::relativeCoor2pxCoor(glm::vec2 pos, glm::vec2 dimensions)
{
	return glm::vec2(((window->getWidth() - dimBackground.x) / 2) + pos.x*dimensions.x, ((window->getHeight() - dimBackground.y) / 2) + dimBackground.y - pos.y*dimensions.y);
}

void Help::onUpdateWindow()
{
	for (Button* b : buttons)
	{
		b->positionPx = relativeCoor2pxCoor(b->positionRel, dimButton);
	}
}