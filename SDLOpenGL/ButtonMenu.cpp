#include "stdafx.h"
#include "ButtonMenu.h"


ButtonMenu::ButtonMenu(LWindow* w, FontManager* fm)
{
	dimButton = glm::vec2(256, 64);
	dimBackground = glm::vec2(1024, 640);
	selectedButton = -1;
	window = w;
	layout = new Layout(dimBackground, 8, 8);
	menuState = LAUNCHERM;

	//launcher elements
	launcherBackground = new Background("./assets/background_launcher.png", dimBackground.x, dimBackground.y);
	launcherButtons = std::vector<Button*>();
	title = new ImageObject(layout->positionObject(glm::vec2(512, 128), 4, 7), 
							glm::vec2(512, 128), 
							new LTexture2D("./assets/title.png", 512, 128));

	//help elements
	helpBackground = new Background("./assets/background_launcher.png", dimBackground.x, dimBackground.y);
	helpButtons = std::vector<Button*>();
	commandsBackground = new ImageObject(layout->positionObject(glm::vec2(770, 400), 4, 5),
										 glm::vec2(770, 400),
										 new LTexture2D("./assets/parchment.png", 770, 400));
	commandsTexts = std::vector<Text*>();
	commandsPics = std::vector<ImageObject*>();
	commandsPics.push_back(new ImageObject(layout->positionObject(glm::vec2(256, 128), 5, 4),
										   glm::vec2(256, 128),
										   new LTexture2D("./assets/dir_arrows.png", 256, 128)));
	commandsPics.push_back(new ImageObject(layout->positionObject(glm::vec2(256, 128), 5, 6),
										   glm::vec2(256, 128),
										   new LTexture2D("./assets/wasd.png", 256, 128)));

	//gameover elements
	gameoverButtons = std::vector<Button*>();

	//victory elements
	victoryButtons = std::vector<Button*>();

	//textElems
	SDL_Color color = { 138, 7, 7 };
	TTF_Font* font = fm->retrieveFont("death_font");
	int size = fm->retrieveSize("death_font");
	gameoverText = new Text(font, "YOU DIED", color, size);
	gameoverText->loadFont();

	color = { 190, 120, 35 };
	font = fm->retrieveFont("main_font");
	size = fm->retrieveSize("main_font");

	Text* startText = new Text(font, "START", color, size);
	startText->loadFont();

	Text* helpText = new Text(font, "HELP", color, size);
	helpText->loadFont();

	Text* backText = new Text(font, "BACK", color, size);
	backText->loadFont();

	Text* restartText = new Text(font, "RETRY", color, size);
	restartText->loadFont();

	Text* exitText = new Text(font, "EXIT", color, size);
	exitText->loadFont();

	color = { 0, 0, 0 };

	Text* attackInfo = new Text(font, "Attack:", color, size);
	attackInfo->loadFont();
	commandsTexts.push_back(attackInfo);

	Text* movementInfo = new Text(font, "Movement:", color, size);
	movementInfo->loadFont();
	commandsTexts.push_back(movementInfo);

	color = { 255, 215, 0 };
	victoryText = new Text(font, "VICTORY", color, size);
	victoryText->loadFont();

	//buttons
	launcherButtons.push_back(new Button(layout->positionObject(dimButton, 4, 4),
										 dimButton,
										 new LTexture2D("./assets/button.png", dimButton.x, dimButton.y),
										 GAME, 
										 startText));
	launcherButtons.push_back(new Button(layout->positionObject(dimButton, 4, 2),
										 dimButton,
										 new LTexture2D("./assets/button.png", dimButton.x, dimButton.y),
										 HELP, 
										 helpText));
	rel2pxButtonsCoor(launcherButtons);

	helpButtons.push_back(new Button(layout->positionObject(dimButton, 4, 1),
									 dimButton,
									 new LTexture2D("./assets/button.png", dimButton.x, dimButton.y),
									 LAUNCHER, 
								  	 backText));
	rel2pxButtonsCoor(helpButtons);

	Button* retryButton = new Button(layout->positionObject(dimButton, 2, 2),
									dimButton,
									new LTexture2D("./assets/button.png", dimButton.x, dimButton.y),
									GAME,
									restartText);
	Button* exitButton = new Button(layout->positionObject(dimButton, 6, 2),
									dimButton,
									new LTexture2D("./assets/button.png", dimButton.x, dimButton.y),
									EXIT,
									exitText);
	gameoverButtons.push_back(retryButton);
	gameoverButtons.push_back(exitButton);
	rel2pxButtonsCoor(gameoverButtons);

	victoryButtons.push_back(retryButton);
	victoryButtons.push_back(exitButton);
	rel2pxButtonsCoor(victoryButtons);
}


void ButtonMenu::render()
{
	glm::vec2 pos;

	switch (menuState)
	{
	case LAUNCHERM:
		launcherBackground->render();
		title->render();
		for (Button* button: launcherButtons)
		{
			button->render();
		}
		break;
		
	case HELPM:
		helpBackground->render();
		commandsBackground->render();
		for (Button* button : helpButtons)
		{
			button->render();
		}
		pos = layout->positionObject(commandsTexts.at(0)->textDimensions, 3, 4);
		commandsTexts.at(0)->drawText(pos.x, pos.y);

		pos = layout->positionObject(commandsTexts.at(1)->textDimensions, 3, 6);
		commandsTexts.at(1)->drawText(pos.x, pos.y);

		for (ImageObject* pic : commandsPics)
		{
			pic->render();
		}
		break;

	case GAMEOVERM:
		for (Button* button : gameoverButtons)
		{
			button->render();
		}
		pos = layout->positionObject(gameoverText->textDimensions, 4, 5);
		gameoverText->drawText(pos.x, pos.y);
		break;

	case VICTORYM:
		for (Button* button : victoryButtons)
		{
			button->render();
		}
		pos = layout->positionObject(victoryText->textDimensions, 4, 5);
		victoryText->drawText(pos.x, pos.y);
		break;

	default: break;
	}
}

void ButtonMenu::rel2pxButtonsCoor(std::vector<Button*> buttonVec)
{
	for (Button* b : buttonVec)
	{
		b->positionPx = relativeCoor2pxCoor(b->positionRel, dimButton);
	}
}

void ButtonMenu::setMenuState(MenuState ms)
{
	selectedButton = -1;
	menuState = ms;
}


void ButtonMenu::selectedCheck(std::vector<Button*> buttons)
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

glm::vec2 ButtonMenu::relativeCoor2pxCoor(glm::vec2 pos, glm::vec2 dimensions)
{
	return glm::vec2(((window->getWidth() - dimBackground.x) / 2) + pos.x*dimensions.x, ((window->getHeight() - dimBackground.y) / 2) + dimBackground.y - pos.y*dimensions.y);
}

void ButtonMenu::onUpdateWindow()
{
	for (Button* b : launcherButtons)
	{
		b->positionPx = relativeCoor2pxCoor(b->positionRel, dimButton);
	}
	for (Button* b : helpButtons)
	{
		b->positionPx = relativeCoor2pxCoor(b->positionRel, dimButton);
	}
	for (Button* b : gameoverButtons)
	{
		b->positionPx = relativeCoor2pxCoor(b->positionRel, dimButton);
	}
	for (Button* b : victoryButtons)
	{
		b->positionPx = relativeCoor2pxCoor(b->positionRel, dimButton);
	}
}

ButtonMenu::~ButtonMenu() {}

float ButtonMenu::centredCoor(float dimPlane, float dimObj)
{
	float result = (dimPlane / dimObj) / 2 - (dimObj / dimObj) / 2;
	return result;
}

