#include "stdafx.h"
#include "Help.h"
#include "Button.h"

//	TODO: [RELEASE] Questa classe non dovrebbe esserci. Tutto ci� � gestibile da un'unica classe Launcher \
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


	SDL_Color color = { 190, 120, 35 };
	background = new Background("./assets/background_launcher.png", 1024, 640);

	TTF_Font* font = font_manager->retrieveFont("main_font");
	int size = font_manager->retrieveSize("main_font");;

	Text* backText = new Text(font, "BACK", color, size);
	backText->loadFont();

	buttons.push_back(new Button(glm::vec2(centredCoor(background->getBackgroundDim().x, dimButton.x), 
					centredCoor(background->getBackgroundDim().y, dimButton.y) - 3), 
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
	background_commands->drawSprite(centredCoor(background->getBackgroundDim().x, 770),centredCoor(background->getBackgroundDim().y, 400) + 0.20, 0, 0);
	int i = 0;
	for (LTexture2D* image : images)
	{
		image->drawSprite(centredCoor(background->getBackgroundDim().x, 256)+0.5, centredCoor(background->getBackgroundDim().y, 128) + 1.25*i++, 0, 0);
	}
	for (Button* button : buttons)
	{
		button->render();
	}
	i = 0;
	for (Text* text : texts)
	{
		text->drawText(centredCoor(background->getBackgroundDim().x, text->textDimensions.x) - 0.75, centredCoor(background->getBackgroundDim().y, text->textDimensions.y) + 4*i++);
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