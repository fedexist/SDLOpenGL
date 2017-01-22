#include "stdafx.h"
#include "Help.h"
#include "Button.h"

//	REFACTOR: [RELEASE] Questa classe non dovrebbe esserci. Tutto ciò è gestibile da un'unica classe Launcher \
	con diversi stati.

Help::Help(LWindow* w, FontManager* font_manager)
{
	texts = std::vector<Text*>();
	buttons = std::vector<Button*>();
	images = std::vector<LTexture2D*> ();
	dimButton = glm::vec2(256, 64);
	dimBackground = glm::vec2(1024, 640);
	selectedButton = -1;
	window = w;
	layout = new Layout(dimBackground, 8, 8);

	SDL_Color color = { 190, 120, 35 };
	background = new Background("./assets/background_launcher.png", 1024, 640);

	TTF_Font* font = font_manager->retrieveFont("main_font");
	int size = font_manager->retrieveSize("main_font");;

	Text* backText = new Text(font, "BACK", color, size);
	backText->loadFont();

	buttons.push_back(new Button(layout->positionObject(dimButton, 4, 1), 
					dimButton, 
					new LTexture2D("./assets/button.png", dimButton.x, dimButton.y), 
					LAUNCHER, backText
					));

	for (Button* b : buttons)
	{
		b->positionPx = relativeCoor2pxCoor(b->positionRel, dimButton);
	}

	images.push_back(new LTexture2D("./assets/dir_arrows.png", 256, 128));
	images.push_back(new LTexture2D("./assets/wasd.png", 256, 128));

	color = { 0, 0, 0 };
	Text* attackInfo = new Text(font, "Attack:", color, size);
	attackInfo->loadFont();
	texts.push_back(attackInfo);

	Text* movementInfo = new Text(font, "Movement:", color, size);
	movementInfo->loadFont();
	texts.push_back(movementInfo);

	background_commands = new LTexture2D("./assets/parchment.png", 770, 400);

	selectedCheck();
}
void Help::render()
{
	background->render();
	glm::vec2 posBgComm = layout->positionObject(glm::vec2(770, 400), 4, 5);
	background_commands->drawSprite(posBgComm.x, posBgComm.y, 0, 0);

	glm::vec2 pos = layout->positionObject(glm::vec2(256, 128), 5, 4);
	images.at(0)->drawSprite(pos.x, pos.y, 0, 0);
	
	pos = layout->positionObject(glm::vec2(256, 128), 5, 6);
	images.at(1)->drawSprite(pos.x, pos.y, 0, 0);

	for (Button* button : buttons)
	{
		button->render();
	}

	pos = layout->positionObject(texts.at(0)->textDimensions, 3, 4);
	texts.at(0)->drawText(pos.x, pos.y);
	
	pos = layout->positionObject(texts.at(1)->textDimensions, 3, 6);
	texts.at(1)->drawText(pos.x, pos.y);
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