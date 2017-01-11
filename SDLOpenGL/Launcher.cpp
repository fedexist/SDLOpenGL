#include "stdafx.h"
#include "Launcher.h"
#include "Button.h"

Launcher::Launcher(LWindow* w, FontManager* font_manager)
{
	SDL_LogDebug(0, "constructing launcher");
	buttons = std::vector<Button*>();
	texts = std::vector<Text*>();
	dimButton = glm::vec2(256, 64);
	dimBackground = glm::vec2(1024,640);
	selectedButton = -1;
	window = w;


	SDL_Color color = { 255, 255, 240 };
	background = new Background("./assets/background_launcher.png", dimBackground.x, dimBackground.y);
	

	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Font is: %s, Size is: %d", &font, *size);

	TTF_Font* font = font_manager->retrieveFont("main_font");
	int size = font_manager->retrieveSize("main_font");

	SDL_LogDebug(0, "building start text");
	Text* startText = new Text(font, "START", color, size);
	SDL_LogDebug(0, "loading font for start text");
	startText->loadFont();

	buttons.push_back(new Button(glm::vec2(centredCoor(background->getBackgroundDim().x, dimButton.x), 
					centredCoor(background->getBackgroundDim().y, dimButton.y) - 1), 
					dimButton, 
					new LTexture2D("./assets/button_start.png", dimButton.x, dimButton.y), 
					GAME, startText
					));

	Text* helpText = new Text(font, "HELP", color, size);
	helpText->loadFont();

	buttons.push_back(new Button(glm::vec2(centredCoor(background->getBackgroundDim().x, dimButton.x), 
					centredCoor(background->getBackgroundDim().y, dimButton.y) - 3), 
					dimButton, 
					new LTexture2D("./assets/button_help.png", dimButton.x, dimButton.y), 
					HELP, helpText));

	for (Button* b : buttons)
	{
		b->positionPx = relativeCoor2pxCoor(b->positionRel, dimButton);
	}
	selectedCheck();

	title = new LTexture2D("./assets/title.png", 512, 128);

	SDL_LogDebug(0, "Finished constructing launcher");
}

void Launcher::render()
{
	background->render();
	title->drawSprite(centredCoor(background->getBackgroundDim().x, 512), centredCoor(background->getBackgroundDim().y, 128) + 1.75, 0, 0);
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
		//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "button: %d", selectedButton);
	}
}

float Launcher::centredCoor(float dimPlane, float dimObj)
{
	float result = (dimPlane / dimObj) / 2 - (dimObj / dimObj) / 2;
	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "result: %f", result);
	return result;
}

glm::vec2 Launcher::relativeCoor2pxCoor(glm::vec2 pos, glm::vec2 dimensions)
{
	return glm::vec2(((window->getWidth() - dimBackground.x) / 2) + pos.x*dimensions.x, ((window->getHeight() - dimBackground.y) / 2) + dimBackground.y - pos.y*dimensions.y);
}

void Launcher::onUpdateWindow()
{
	for (Button* b : buttons)
	{
		b->positionPx = relativeCoor2pxCoor(b->positionRel, dimButton);
	}
}