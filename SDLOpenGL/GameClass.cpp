#include "stdafx.h"
#include "GameClass.h"
#include <fstream>
#include "Player.h"
#include "Fire.h"
#include "Chest.h"
#include "Door.h"
#include "Portal.h"
#include "AI.h"


GameClass::GameClass(std::string title)
{

	windowTitle = title;
	plane = DrawingPlane();
	cachedLevelLayouts = std::vector< std::vector<GLuint*> >();
	gameObjectArray = std::vector<GameObject*>();
	allObjectsFactory = std::vector<GameObject*>();
	allAisArray = std::vector<AI*>();
	allTextures = std::vector<LTexture2D>();
	allChestsArray = std::vector<Chest*>();
	allEnemiesArray = std::vector<Player*>();
	gameState = LAUNCHER;
}

GameClass::GameClass()
{
}

GameClass::~GameClass()
{

}


void GameClass::update(float dt)
{
	
	if(gameState == GAME)
	{

		//Update World Knowledge of the world to all the actors to get collisions working
		setObjectWorldKnowledge(player_);
		for (Player* enemy : allEnemiesArray)
			setObjectWorldKnowledge(enemy);

		//Update AIs bound to NPC actors for pathfinding
		AIHandicapCounter++;
		if (AIHandicapCounter == AIHandicapAI)
		{
			for (AI* currentAI : allAisArray)
			{
				currentAI->update(distance(currentAI->myCharacter, player_), dt);
			}
			AIHandicapCounter = 0;
		}
		
		for (int i = 0; i < gameObjectArray.size(); i++)
		{
			gameObjectArray[i]->areaSharing.clear();
		}

		
		//Update detection Y coordinate for rendering order
		for (int i = 0; i < gameObjectArray.size(); i++)
		{
			float ll, rl, ul, dl;
			ll = gameObjectArray[i]->position.x - gameObjectArray[i]->hitboxDimensions.x;
			rl = gameObjectArray[i]->position.x + gameObjectArray[i]->hitboxDimensions.x;
			dl = gameObjectArray[i]->position.y;// - gameObjectArray.at(i)->hitboxDimensions.y;
			ul = gameObjectArray[i]->position.y + gameObjectArray[i]->hitboxDimensions.y;

			for (int j = i + 1; j < gameObjectArray.size(); j++)
			{
				float llj, rlj, ulj, dlj;
				llj = gameObjectArray[j]->position.x - gameObjectArray[j]->hitboxDimensions.x;
				rlj = gameObjectArray[j]->position.x + gameObjectArray[j]->hitboxDimensions.x;
				ulj = gameObjectArray[j]->position.y;// - gameObjectArray.at(j)->hitboxDimensions.y;
				dlj = gameObjectArray[j]->position.y + gameObjectArray[j]->hitboxDimensions.y;
				bool XAligned = (rl <= rlj && rl >= llj) || (ll <= rlj && ll >= llj);
				bool YAligned = (dl <= dlj && dl >= ulj) || (ul <= dlj && ul >= ulj);

				if (XAligned && YAligned)
				{
					gameObjectArray[i]->areaSharing.push_back(gameObjectArray[j]);

					gameObjectArray[j]->areaSharing.push_back(gameObjectArray[i]);
				}
			}

			gameObjectArray[i]->update(dt);
			//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "I'm in the update function of GameClass, current delta is: %f\n", dt);

			if (player_->isDead())
			{
				//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "CenterDummy pos: %f, %f", centerDummy->position.x, centerDummy->position.y);
				setGameState(GAMEOVER);
			}
			if (!player_->visible)
			{
				if (timerToWin == 0)
					timerToWin = SDL_GetTicks();
				if (SDL_GetTicks() - timerToWin > 2000)
					setGameState(VICTORY);
			}
		}
	}
	if (player_->visible)
		camera->update(dt);

}

//Loads to memory texture and sound assets
//Fill ObjectsFactory
//Populates World
void GameClass::loadMedia()
{
	plane.loadMedia();

	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "About to loadLevelLayout()\n");
	loadLevelLayout("room1", 40, 40);

	// REFACTOR: Using an hashmap is better and makes easier to retrieve a texture
	//Caricamento textures
	allTextures.push_back(LTexture2D("./assets/fire.png",64,64,120));
	allTextures.push_back(LTexture2D("./assets/player.png", 64, 64, 60));
	allTextures.push_back(LTexture2D("./assets/life2.png", 64, 64,120));
	allTextures.push_back(LTexture2D("./assets/orc.png", 64, 64, 60));
	allTextures.push_back(LTexture2D("./assets/chest.png", 64, 64, 60));	
	allTextures.push_back(LTexture2D("./assets/door.png", 64, 64, 60));
	allTextures.push_back(LTexture2D("./assets/portal.png", 64, 64, 60));

	// REFACTOR: Using an hashmap is better and makes easier to retrieve a GameObject
	allObjectsFactory.push_back(new Fire(glm::vec2(0.0, 0.0), glm::vec2(0, 0), glm::vec2(64, 64), true, true, &allTextures.at(0), 0.05, 0, 4));
	allObjectsFactory.push_back(new Player(glm::vec2(0.0, 0.0), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, &allTextures.at(3), 1, 26, 28));
	allObjectsFactory.push_back(new HealthBar(glm::vec2(0.0, 0.0), glm::vec2(0, 0), glm::vec2(64, 64), true, true, &allTextures.at(2), 0.05, 0, 1));
	
	allObjectsFactory.push_back(new Chest(glm::vec2(0.0, 0.0), glm::vec2(0, 0), glm::vec2(64, 64), true, true, &allTextures.at(4), 0.05, 0, 1, audio_manager));

	allObjectsFactory.push_back(new Door(glm::vec2(0.0, 0.0), glm::vec2(0, 0), glm::vec2(64, 64), true, true, &allTextures.at(5), 0.05, 0, 5, audio_manager));
	
	
	allObjectsFactory.push_back(new Portal(glm::vec2(0.0, 0.0), glm::vec2(0, 0), glm::vec2(64, 64), true, true, &allTextures.at(6), 0.05, 6, 7, audio_manager));
	allObjectsFactory.push_back(new Portal(glm::vec2(0.0, 0.0), glm::vec2(0, 0), glm::vec2(64, 64), true, true, &allTextures.at(6), 0.05, 7, 8, audio_manager));
	allObjectsFactory.push_back(new Portal(glm::vec2(0.0, 0.0), glm::vec2(0, 0), glm::vec2(64, 64), true, true, &allTextures.at(6), 0.05, 3, 4, audio_manager));
	allObjectsFactory.push_back(new Portal(glm::vec2(0.0, 0.0), glm::vec2(0, 0), glm::vec2(64, 64), true, true, &allTextures.at(6), 0.05, 2, 3, audio_manager));


	audio_manager->LoadMusic("./assets/music/journeys.mp3","MainTheme");
	audio_manager->LoadMusic("./assets/music/castlejam.mp3", "LauncherTheme");
	audio_manager->LoadMusic("./assets/music/victory_theme.mp3", "VictoryTheme");
	audio_manager->LoadSoundEffect("./assets/sfx/swish.wav", "SwordSwish");
	audio_manager->LoadSoundEffect("./assets/sfx/buttonsel.wav", "ButtonSelected");
	audio_manager->LoadSoundEffect("./assets/sfx/door_open_004.wav", "OpenChest");
	audio_manager->LoadSoundEffect("./assets/sfx/teleport.wav", "OpenPortal");
	audio_manager->LoadSoundEffect("./assets/sfx/death_effect.wav", "DeathEffect");
	audio_manager->setMusicVolume(0.75f);

	audio_manager->ManageMusic(PLAY, "LauncherTheme", MIX_FADING_IN, 3000);

	populateWorld();
	camera->follow(centerDummy);
}

void GameClass::render()
{
	switch (gameState)
	{
	case GAME:
		plane.render(&currentLevelLayout, levelLayoutW, levelLayoutH);
		sort(gameObjectArray.begin(), gameObjectArray.end(), gameObjectArray.at(0)->gameObjectComparer);

		// REFACTOR 2 different unary_functions, renderer and noPortalRender might be too much -> functors are probably better

		std::for_each(portalArray.begin(), portalArray.end(), renderer());

		std::for_each(gameObjectArray.begin(), gameObjectArray.end(), noPortalRenderer());

		break;
	default:
		menu->render();
		break;
	}
}

void GameClass::loadLevelLayout(std::string levelName, unsigned int width, unsigned int height)
{
	currentLevelLayout.clear();
	currentLevelLayout_l.clear();
	currentLevelLayout_o.clear();

	levelLayoutW = width;
	levelLayoutH = height;

	for (int i = 0; i < height; ++i)
	{
		currentLevelLayout.push_back(new GLuint[width]);
		currentLevelLayout_l.push_back(new GLint[width]);
		currentLevelLayout_o.push_back(new GLint[width]);
	}
		

	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Initialised currentlevellayout");



	std::ifstream file(levelPath + levelName + "_tiles.csv");

	for(int row = 0; row < height; ++row)
	{
		std::string line;
		getline(file, line);
			
		std::stringstream iss(line);

		for (int col = 0; col < width; ++col)
		{
			std::string val;
			getline(iss, val, ',');
			
			currentLevelLayout[row][col] = stoi(val);
			
		}
		
	}

	std::ifstream filel(levelPath + levelName + "_logic.csv");

	for (int row = 0; row < height; ++row)
	{
		std::string line;
		getline(filel, line);

		std::stringstream iss(line);

		for (int col = 0; col < width; ++col)
		{
			std::string val;
			getline(iss, val, ',');

			currentLevelLayout_l[row][col] = stoi(val);

		}

	}

	std::ifstream fileo(levelPath + levelName + "_objects.csv");

	for (int row = 0; row < height; ++row)
	{
		std::string line;
		getline(fileo, line);

		std::stringstream iss(line);

		for (int col = 0; col < width; ++col)
		{
			std::string val;
			getline(iss, val, ',');

			currentLevelLayout_o.at(row)[col] = stoi(val);

		}

	}

	cachedLevelLayouts.push_back(currentLevelLayout);
	cachedLevelLayouts_l.push_back(currentLevelLayout_l);
	cachedLevelLayouts_o.push_back(currentLevelLayout_o);

}

void GameClass::populateWorld()
{
	//3,1
	player_ = new Player(glm::vec2(3, 1), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, &allTextures.at(1), 1, 26, 28);

	player_->isPlayer = true;

	Portal* portalUpLeft = nullptr;
	Portal* portalDownLeft = nullptr;
	Portal* portalUpRight = nullptr;
	Portal* portalDownRight = nullptr;


	for (int j = 0; j < levelLayoutH; j++)
	{
		for (int i = 0; i < levelLayoutW; i++)
		{
			int objectIndex = currentLevelLayout_o[j][i];
			if (objectIndex > -1)
			{
				Fire* fireThis = dynamic_cast<Fire*>(allObjectsFactory[objectIndex]);
				Player* playerThis = dynamic_cast<Player*>(allObjectsFactory[objectIndex]);
				Chest* chestThis = dynamic_cast<Chest*>(allObjectsFactory[objectIndex]);
				Door* doorThis = dynamic_cast<Door*>(allObjectsFactory[objectIndex]);
				Portal* portalThis = dynamic_cast<Portal*>(allObjectsFactory[objectIndex]);
				
				if (portalThis)
				{
					if (portalThis->startingIndexFrame == 2)
						portalUpLeft = new Portal(glm::vec2(i, (levelLayoutH - j - 1)), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, 1.0, static_cast<Portal*>(allObjectsFactory.at(objectIndex)));

					if (portalThis->startingIndexFrame == 3)
						portalUpRight = new Portal(glm::vec2(i, (levelLayoutH - j - 1)), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, 1.0, static_cast<Portal*>(allObjectsFactory.at(objectIndex)));

					if (portalThis->startingIndexFrame == 6)
						portalDownLeft = new Portal(glm::vec2(i, (levelLayoutH - j - 1)), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, 1.0, static_cast<Portal*>(allObjectsFactory.at(objectIndex)));

					if (portalThis->startingIndexFrame == 7)
						portalDownRight = new Portal(glm::vec2(i, (levelLayoutH - j - 1)), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, 1.0, static_cast<Portal*>(allObjectsFactory.at(objectIndex)));

				}

				if (fireThis)
				{
					Fire* creatingFire = new Fire(glm::vec2(i, (levelLayoutH - j - 1)), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, 1.0, static_cast<Fire*>(allObjectsFactory.at(objectIndex)));
					creatingFire->resizeHitBox(glm::vec2(0.5, 1));
					gameObjectArray.push_back(creatingFire);
				
				}

				if (chestThis)
				{
					Chest* creatingChest = new Chest(glm::vec2(i, (levelLayoutH - j - 1)), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, 1.0, static_cast<Chest*>(allObjectsFactory.at(objectIndex)));
					//creatingChest->resizeHitBox(glm::vec2(0.5,1));
					gameObjectArray.push_back(creatingChest);
					allChestsArray.push_back(creatingChest);

				}

				if (doorThis)
				{
					Door* creatingDoor = new Door(glm::vec2(i, (levelLayoutH - j - 1)), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, 1.0, static_cast<Door*>(allObjectsFactory.at(objectIndex)));
					//creatingChest->resizeHitBox(glm::vec2(0.5,1));
					gameObjectArray.push_back(creatingDoor);
				}

				if (playerThis)
				{

					Player* creatingPlayer = new Player(glm::vec2(i, (levelLayoutH - j - 1)), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, 1.00002, static_cast<Player*>(allObjectsFactory.at(objectIndex)));

					creatingPlayer->myHealthBar = new HealthBar(glm::vec2(i, (levelLayoutH - j - 1) + 1), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, 1.0, static_cast<HealthBar*>(allObjectsFactory.at(2)));
					creatingPlayer->myHealthBar->attachedTo = creatingPlayer;
					gameObjectArray.push_back(creatingPlayer);
					gameObjectArray.push_back(creatingPlayer->myHealthBar);
					allEnemiesArray.push_back(creatingPlayer);

					AI* enemyAI = new AI(creatingPlayer, player_, audio_manager);
					enemyAI->updateWorld(currentLevelLayout_l, currentLevelLayout_o, levelLayoutH, levelLayoutW);
					allAisArray.push_back(enemyAI);
				}

			}
		}
	}

	portalSetup(portalUpLeft, portalUpRight, portalDownLeft, portalDownRight);

	centerDummy = new Player(glm::vec2(menu->centredCoor(1024, 64), menu->centredCoor(640, 64)), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, &allTextures.at(1), 1, 26, 28);
	HealthBar* playerHealthBar = new HealthBar(glm::vec2(4.5, 5.0), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, 1.0, static_cast<HealthBar*>(allObjectsFactory.at(2)));
	playerHealthBar->attachedTo = player_;
	player_->myHealthBar = playerHealthBar;
	gameObjectArray.push_back(player_);
	gameObjectArray.push_back(player_->myHealthBar);

	std::srand(std::time(nullptr));

	std::vector<int> chestIndexRandomized;
	for (int i = 0; i < allChestsArray.size(); i++)
	{
		chestIndexRandomized.push_back(i);
	}

	std::random_shuffle(chestIndexRandomized.begin(), chestIndexRandomized.end());

	for (int i = 0; i < allChestsArray.size(); i++)
	{
		Chest* thisChest = allChestsArray[chestIndexRandomized[i]];

		if (i < 2)
			thisChest->addTreasure(Chest::KEY);
		else
			thisChest->addTreasure(Chest::COIN);

	}
}

void GameClass::emptyWorld()
{
	
	std::for_each (gameObjectArray.begin (), gameObjectArray.end (), deleter<GameObject> ());
	std::for_each (allAisArray.begin (), allAisArray.end (), deleter<AI> ());
	
	gameObjectArray.clear();	
	allChestsArray.clear();	
	allEnemiesArray.clear();
	portalArray.clear();
	allAisArray.clear();
	
}

void GameClass::portalSetup(Portal* portalUpLeft, Portal* portalUpRight, Portal* portalDownLeft, Portal* portalDownRight)
{
	if (portalUpLeft!= nullptr)
	{
		portalUpLeft->UpLeft = portalUpLeft;
		portalUpRight->UpLeft = portalUpLeft;
		portalDownLeft->UpLeft = portalUpLeft;
		portalDownRight->UpLeft = portalUpLeft;

		portalUpLeft->Next = portalUpRight;
		portalUpRight->Next = portalDownLeft;
		portalDownLeft->Next = portalDownRight;
		portalDownRight->Next = nullptr;

		portalArray.push_back(portalUpLeft);
		portalArray.push_back(portalUpRight);
		portalArray.push_back(portalDownLeft);
		portalArray.push_back(portalDownRight);
		gameObjectArray.push_back(portalUpLeft);
		gameObjectArray.push_back(portalUpRight);
		gameObjectArray.push_back(portalDownLeft);
		gameObjectArray.push_back(portalDownRight);

	}


}


void GameClass::handleEvents(SDL_Event& e)
{
	handleKeyboardEvents();
	handleMouseEvents(e);
	
}

void GameClass::handleMouseEvents(const SDL_Event& e)
{
	if ((e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) && gameState != GAME)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		menu->selectedButton = -1;

		switch (menu->menuState)
		{
		case LAUNCHERM:
		{
			menu->selectedCheck(menu->launcherButtons);
			for (int i = 0; i < menu->launcherButtons.size(); i++)
			{

				Button* b = menu->launcherButtons.at(i);
				if (b->isInside(x, y))
				{
					menu->selectedButton = i;
					menu->selectedCheck(menu->launcherButtons);

					if (e.type == SDL_MOUSEBUTTONUP && menu->selectedButton == i)
					{
						audio_manager->playSoundEffect("ButtonSelected");
						setGameState(menu->launcherButtons.at(menu->selectedButton)->getOnClickTransition());
					}
				}
			}
			break;
			}	
		case HELPM:
		{
			menu->selectedCheck(menu->helpButtons);
			for (int i = 0; i < menu->helpButtons.size(); i++)
			{

				Button* b = menu->helpButtons.at(i);
				if (b->isInside(x, y))
				{
					menu->selectedButton = i;
					menu->selectedCheck(menu->helpButtons);

					if (e.type == SDL_MOUSEBUTTONUP && menu->selectedButton == i)
					{
						audio_manager->playSoundEffect("ButtonSelected");
						setGameState(menu->helpButtons.at(menu->selectedButton)->getOnClickTransition());
					}
				}
			}
			break;
			}
		case GAMEOVERM:
		{
			menu->selectedCheck(menu->gameoverButtons);
			for (int i = 0; i < menu->gameoverButtons.size(); i++)
			{

				Button* b = menu->gameoverButtons.at(i);
				if (b->isInside(x, y))
				{
					menu->selectedButton = i;
					menu->selectedCheck(menu->gameoverButtons);

					if (e.type == SDL_MOUSEBUTTONUP && menu->selectedButton == i)
					{
						audio_manager->playSoundEffect("ButtonSelected");
						setGameState(menu->gameoverButtons.at(menu->selectedButton)->getOnClickTransition());
					}
				}
			}
			break;
		}
		case VICTORYM:
		{
			menu->selectedCheck(menu->victoryButtons);
			for (int i = 0; i < menu->victoryButtons.size(); i++)
			{

				Button* b = menu->victoryButtons.at(i);
				if (b->isInside(x, y))
				{
					menu->selectedButton = i;
					menu->selectedCheck(menu->victoryButtons);

					if (e.type == SDL_MOUSEBUTTONUP && menu->selectedButton == i)
					{
						audio_manager->playSoundEffect("ButtonSelected");
						setGameState(menu->victoryButtons.at(menu->selectedButton)->getOnClickTransition());
					}
				}
			}
			break;
		}
		default:
		{
			break;
			}
		}
	}
}

void GameClass::handleKeyboardEvents()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

	switch (gameState)
	{
		case GAME:
		{
			if (!player_->visible)
				return;
			bool cooldownBool = int (SDL_GetTicks() - player_->coolDown) > 0;
			bool isMoving = currentKeyStates[SDL_SCANCODE_W] || currentKeyStates[SDL_SCANCODE_A] || currentKeyStates[SDL_SCANCODE_S] || currentKeyStates[SDL_SCANCODE_D];
			bool isSlashing = cooldownBool && (currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_RIGHT]);

			if (isMoving)
			{
				glm::vec2 uDlR = glm::vec2(-1, -1);
				if (currentKeyStates[SDL_SCANCODE_W])
				{
					uDlR.y = UP;
				}
				else if (currentKeyStates[SDL_SCANCODE_S])
				{
					uDlR.y = DOWN;
				}
				if (currentKeyStates[SDL_SCANCODE_A])
				{
					uDlR.x = LEFT;
				}
				else if (currentKeyStates[SDL_SCANCODE_D])
				{
					uDlR.x = RIGHT;
				}
				
				if (isSlashing)
				{
					glm::vec2 uDlRHit = glm::vec2(-1, -1);

					if (currentKeyStates[SDL_SCANCODE_UP])
					{
						uDlRHit.y = UP;
					}
					else if (currentKeyStates[SDL_SCANCODE_DOWN])
					{
						uDlRHit.y = DOWN;
					}
					if (currentKeyStates[SDL_SCANCODE_LEFT])
					{
						uDlRHit.x = LEFT;
					}
					else if (currentKeyStates[SDL_SCANCODE_RIGHT])
					{
						uDlRHit.x = RIGHT;
					}
						//SDL_LogDebug(0, "in the slashmove loop");
					player_->coolDown = SDL_GetTicks() + 400;
					player_->Act(MOVING_SLASHING, uDlR, uDlRHit);
					audio_manager->playSoundEffect("SwordSwish");
				}
				else
				{
					player_->Act(MOVING, uDlR);
					//SDL_LogDebug(0, "in the move loop");
				}

			}
			else if (isSlashing && !isMoving)
			{
				//SDL_LogDebug(0, "SLASHING NOT MOVING, %d");
				glm::vec2 uDlR = glm::vec2(-1, -1);
				if (currentKeyStates[SDL_SCANCODE_UP])
				{
					uDlR.y = UP;
				}
				else if (currentKeyStates[SDL_SCANCODE_DOWN])
				{
					uDlR.y = DOWN;
				}
				if (currentKeyStates[SDL_SCANCODE_LEFT])
				{
					uDlR.x = LEFT;
				}
				else if (currentKeyStates[SDL_SCANCODE_RIGHT])
				{
					uDlR.x = RIGHT;
				}
				player_->coolDown = SDL_GetTicks() + 400;
				player_->Act(SLASHING, uDlR);
				audio_manager->playSoundEffect("SwordSwish");
			}
			if (!(isMoving || isSlashing))
			{
				player_->Act(IDLE, glm::vec2(-1, -1));
			}
			break;
		}
		default:
		{
			break;
		}
	}
}

void GameClass::setObjectWorldKnowledge(GameObject * actor)
{
	int centerX, centerY;
	centerY = actor->currentCell().y;
	centerX = actor->currentCell().x;

	int currentGridCellY = 0, currentGridCellX; // cella in basso a sinistra

	//SDL_LogDebug(0, "Setting Object World Knowledge");

	for(int j = -1; j <= 1; j++)
	{
		currentGridCellX = 0;

		for(int i = -1; i <= 1; i++)
		{
			if( centerX + i < 0 || centerX + i >= levelLayoutW || centerY + j < 0 || centerY + j >= levelLayoutH)
			{
				actor->currentWorldKnowledge[currentGridCellY][currentGridCellX] = -1;
				currentGridCellX++;
				continue;
			}

			actor->currentWorldKnowledge[currentGridCellY][currentGridCellX] = currentLevelLayout_l[levelLayoutH - (centerY + j) - 1][centerX + i];
			currentGridCellX++;
		}
		currentGridCellY++;
	}
	
	//SDL_LogDebug(0, "Finished Setting Object World Knowledge");

	
}


void GameClass::setGameState(GameState gs)
{
	switch (gs)
	{
		case LAUNCHER:
		{
			menu->setMenuState(LAUNCHERM);
			break;
		}
		case HELP:
		{
			menu->setMenuState(HELPM);
			break;
		}
		case GAME:
		{
			if(gameState == GAMEOVER || gameState == VICTORY)
			{
				SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "About to repopulate world after gameover");
				populateWorld();
			}
				

			audio_manager->ManageMusic(STOP, "LauncherTheme");
			audio_manager->ManageMusic(PLAY, "MainTheme", MIX_FADING_IN, 3000);

			camera->resetProjection(window->getWidth(), window->getHeight());
			if (player_->visible)
				camera->follow(player_);

			break;
		}
		case GAMEOVER:
		{
			menu->setMenuState(GAMEOVERM);
			audio_manager->setEffectsVolume(0.4f);
			audio_manager->ManageMusic(STOP, "MainTheme");
			audio_manager->playSoundEffect("DeathEffect");
			
			camera->follow(centerDummy);
			camera->resetProjection(window->getWidth(), window->getHeight());
			emptyWorld();
	
			break;
		}
		case VICTORY:
		{
			menu->setMenuState(VICTORYM);
			audio_manager->ManageMusic(STOP, "MainTheme");
			audio_manager->ManageMusic(PLAY, "VictoryTheme", MIX_FADING_IN, 3000);
			
			camera->follow(centerDummy);
			camera->resetProjection(window->getWidth(), window->getHeight());
			emptyWorld();

			break;
		}
		case EXIT:
		{
			quit();
		}
		default:
		{
			break;
		}
	}
	gameState = gs;
}

void GameClass::setAudioManager(AudioManager* audio_manager)
{
	this->audio_manager = audio_manager;
}


float GameClass::distance(GameObject* obj1, GameObject* obj2) const
{

	glm::vec2 position1 = obj1->spriteCenter();
	glm::vec2 position2 = obj2->spriteCenter();

	return glm::distance2(position1, position2);

}

void GameClass::setCamera2D(Camera2D* camera_)
{
	camera = camera_;
}

void GameClass::setFontManager(FontManager* font_manager)
{
	this->font_manager = font_manager;
}

//Push into SDL_Event Stack a quit event, which is managed by the EventHandler
void GameClass::quit()
{
	SDL_Event* quit = new SDL_Event();
	quit->type = SDL_QUIT;
	SDL_PushEvent(quit);

}
