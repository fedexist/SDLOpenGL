#include "stdafx.h"
#include "DeathMenu.h"


DeathMenu::DeathMenu(LWindow* w, FontManager* font_manager)
{
	buttons = std::vector<Button*>();
	dimButton = glm::vec2(256, 64);
	dimBackground = glm::vec2(1024, 640);
	selectedButton = -1;
	window = w;
	layout = new Layout(dimBackground, 8, 8);

	SDL_Color color = { 138, 7, 7 };

	TTF_Font* font = font_manager->retrieveFont("death_font");
	int size = font_manager->retrieveSize("death_font");

	deathText = new Text(font, "YOU DIED", color, size);
	deathText->loadFont();

	color = { 190, 120, 35 };

	font = font_manager->retrieveFont("main_font");
	size = font_manager->retrieveSize("main_font");;

	Text* restartText = new Text(font, "RETRY", color, size);
	restartText->loadFont();

	buttons.push_back(new Button(layout->positionObject(dimButton, 2, 2),
		dimButton,
		new LTexture2D("./assets/button.png", dimButton.x, dimButton.y),
		GAME, restartText
		));

	Text* exitText = new Text(font, "EXIT", color, size);
	exitText->loadFont();

	buttons.push_back(new Button(layout->positionObject(dimButton, 6, 2),
		dimButton,
		new LTexture2D("./assets/button.png", dimButton.x, dimButton.y),
		EXIT, exitText
		));

	for (Button* b : buttons)
	{
		b->positionPx = relativeCoor2pxCoor(b->positionRel, dimButton);
	}

	selectedCheck();
}
void DeathMenu::render()
{
	glm::vec2 textPos = layout->positionObject(deathText->textDimensions, 4, 5);
	deathText->drawText(textPos.x, textPos.y);
	for (Button* button : buttons)
	{
		button->render();
	}
}

DeathMenu::~DeathMenu()
{
}

void DeathMenu::selectedCheck()
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

glm::vec2 DeathMenu::relativeCoor2pxCoor(glm::vec2 pos, glm::vec2 dimensions)
{
	return glm::vec2(((window->getWidth() - dimBackground.x) / 2) + pos.x*dimensions.x, ((window->getHeight() - dimBackground.y) / 2) + dimBackground.y - pos.y*dimensions.y);
}

void DeathMenu::onUpdateWindow()
{
	for (Button* b : buttons)
	{
		b->positionPx = relativeCoor2pxCoor(b->positionRel, dimButton);
	}
}
