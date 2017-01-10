#include "stdafx.h"
#include "GameClass.h"
#include <fstream>
#include "Player.h"
#include "Fire.h"
#include "Chest.h"
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
		setObjectWorldKnowledge(player_); //dovrebbe essere fatto per ogni actor
		for (int i = 0; i < allAisArray.size(); i++)
		{

			allAisArray.at(i)->update(distance(allAisArray.at(i)->myCharacter, player_), dt, currentLevelLayout_l, currentLevelLayout_o, levelLayoutH,levelLayoutW);
		}
		for (int i = 0; i < gameObjectArray.size(); i++)
		{
			gameObjectArray.at(i)->areaSharing.clear();
		}
		for (int i = 0; i < gameObjectArray.size(); i++)
		{
			float ll, rl, ul, dl;
			ll = gameObjectArray.at(i)->position.x - gameObjectArray.at(i)->hitboxDimensions.x;
			rl = gameObjectArray.at(i)->position.x + gameObjectArray.at(i)->hitboxDimensions.x;
			dl = gameObjectArray.at(i)->position.y;// - gameObjectArray.at(i)->hitboxDimensions.y;
			ul = gameObjectArray.at(i)->position.y + gameObjectArray.at(i)->hitboxDimensions.y;
			for (int j = i + 1; j < gameObjectArray.size(); j++)
			{
				float llj, rlj, ulj, dlj;
				llj = gameObjectArray.at(j)->position.x - gameObjectArray.at(j)->hitboxDimensions.x;
				rlj = gameObjectArray.at(j)->position.x + gameObjectArray.at(j)->hitboxDimensions.x;
				ulj = gameObjectArray.at(j)->position.y;// - gameObjectArray.at(j)->hitboxDimensions.y;
				dlj = gameObjectArray.at(j)->position.y + gameObjectArray.at(j)->hitboxDimensions.y;
				bool XAligned = (rl <= rlj && rl >= llj) || (ll <= rlj && ll >= llj);
				bool YAligned = (dl <= dlj && dl >= ulj) || (ul <= dlj && ul >= ulj);
				/*if (XAligned )
				{
				SDL_LogDebug(0,"XAligned");
				}
				if (YAligned)
				{
				SDL_LogDebug(0, "YAligned");
				}*/

				if (XAligned && YAligned)
				{
					gameObjectArray.at(i)->areaSharing.push_back(gameObjectArray.at(j));

					gameObjectArray.at(j)->areaSharing.push_back(gameObjectArray.at(i));
				}
			}

			Fire* fireThis = dynamic_cast<Fire*>(gameObjectArray.at(i));
			Player* playerThis = dynamic_cast<Player*>(gameObjectArray.at(i));
			//HealthBar* healthThis = dynamic_cast<HealthBar*>(gameObjectArray.at(i));
			/*
			if (fireThis)
			{
			fireThis->update(dt);
			}
			if (playerThis)
			{
			playerThis->update(dt);
			}
			*/
			gameObjectArray.at(i)->update(dt);
			//player_->update(dt);
			//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "I'm in the update function of GameClass, current delta is: %f\n", dt);
		}
	}

	camera->update(dt);

}


void GameClass::loadMedia()
{
	//AllGameResources.loadMedia(sdl_renderer)
	plane.loadMedia();

	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "About to loadLevelLayout()\n");
	loadLevelLayout("room1", 40, 40);

	//Caricamento textures
	allTextures.push_back(LTexture2D("./assets/CampFireFinished.png",64,64,60));
	allTextures.push_back(LTexture2D("./assets/player.png", 64, 64, 60));
	allTextures.push_back(LTexture2D("./assets/life.png", 64, 64,60));

	allTextures.push_back(LTexture2D("./assets/orc.png", 64, 64, 60));
	allTextures.push_back(LTexture2D("./assets/chest.png", 64, 64, 60));

	allObjectsFactory.push_back(new Fire(glm::vec2(0.0, 0.0), glm::vec2(0, 0), glm::vec2(64, 64), true, true, &allTextures.at(0), 0.05, 0, 4));
	allObjectsFactory.push_back(new Player(glm::vec2(0.0, 0.0), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, &allTextures.at(3), 1, 26, 28));
	allObjectsFactory.push_back(new HealthBar(glm::vec2(0.0, 0.0), glm::vec2(0, 0), glm::vec2(64, 64), true, true, &allTextures.at(2), 0.05, 0, 4));
	
	allObjectsFactory.push_back(new Chest(glm::vec2(0.0, 0.0), glm::vec2(0, 0), glm::vec2(64, 64), true, true, &allTextures.at(4), 0.05, 0, 1));

	player_ = new Player(glm::vec2(4.5, 4.5), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, &allTextures.at(1), 1, 26, 28);

	player_->isPlayer = true;

	for (int j = 0; j < levelLayoutH; j++)
	{
		for (int i = 0; i < levelLayoutW; i++)
		{
			int objectIndex = currentLevelLayout_o.at(j)[i];
			if (objectIndex > -1)
			{
				Fire* fireThis = dynamic_cast<Fire*>(allObjectsFactory.at(objectIndex));
				Player* playerThis = dynamic_cast<Player*>(allObjectsFactory.at(objectIndex));
				Chest* chestThis = dynamic_cast<Chest*>(allObjectsFactory.at(objectIndex));

				if (fireThis)
				{
					Fire* creatingFire = new Fire(glm::vec2(i, (levelLayoutH - j - 1)), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, 1.0, static_cast<Fire*>(allObjectsFactory.at(objectIndex)));
					creatingFire->resizeHitBox(glm::vec2(0.5,1));
					gameObjectArray.push_back (creatingFire);
				}

				if (chestThis)
				{
					Chest* creatingChest = new Chest(glm::vec2(i, (levelLayoutH - j - 1)), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, 1.0, static_cast<Chest*>(allObjectsFactory.at(objectIndex)));
					//creatingChest->resizeHitBox(glm::vec2(0.5,1));
					gameObjectArray.push_back (creatingChest);
				}

				if (playerThis)
				{

					Player* creatingPlayer = new Player(glm::vec2(i, (levelLayoutH - j - 1)), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, 1.00002, static_cast<Player*>(allObjectsFactory.at(objectIndex)));

					creatingPlayer->myHealthBar = new HealthBar(glm::vec2(i, (levelLayoutH - j - 1)+1), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, 1.0, static_cast<HealthBar*>(allObjectsFactory.at(2)));
					creatingPlayer->myHealthBar->attachedTo = creatingPlayer;
					gameObjectArray.push_back(creatingPlayer);
					gameObjectArray.push_back(creatingPlayer->myHealthBar);
					 
					allAisArray.push_back(new AI(creatingPlayer, player_));
				}

			}
		}
	}
	/*
	player_ = new Player(glm::vec2(4.5, 4.5), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, &allTextures.at(1), 1, 26, 28);
	player_->isPlayer = true;
	*/

	centerDummy = new Player(glm::vec2(launcher->centredCoor(1024, 64), launcher->centredCoor(640, 64)), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, &allTextures.at(1), 1, 26, 28);

	HealthBar* playerHealthBar = new HealthBar(glm::vec2(4.5, 5.0), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, 1.0, static_cast<HealthBar*>(allObjectsFactory.at(2)));
	playerHealthBar->attachedTo =player_;
	player_->myHealthBar = playerHealthBar;
	gameObjectArray.push_back(player_); 
	gameObjectArray.push_back(player_->myHealthBar);

	audio_manager->LoadMusic("./assets/music/journeys.mp3","MainTheme");
	audio_manager->LoadMusic("./assets/music/castlejam.mp3", "LauncherTheme");
	audio_manager->LoadSoundEffect("./assets/sfx/swish.wav", "SwordSwish");
	audio_manager->LoadSoundEffect("./assets/sfx/buttonsel.wav", "ButtonSelected");
	audio_manager->setMusicVolume(0.75f);

	audio_manager->ManageMusic(PLAY, "LauncherTheme", MIX_FADING_IN, 3000);
}

void GameClass::render()
{
	switch (gameState)
	{
	case LAUNCHER:
		launcher->render();
		break;
	case HELP:
		help->render();
		break;
	case GAME:
		plane.render(&currentLevelLayout, levelLayoutW, levelLayoutH);
		sort(gameObjectArray.begin(), gameObjectArray.end(), gameObjectArray.at(0)->gameObjectComparer);
		for (int i = 0; i < gameObjectArray.size(); i++)
		{
			//if (gameObjectArray.at(i)->isPlayer)
			//	((Player*)gameObjectArray.at(i))->render();
			//else
				gameObjectArray.at(i)->render();
		}
		break;
	default:
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
		
		
		//if ( !file.good() )
			//break;

		std::stringstream iss(line);

		for (int col = 0; col < width; ++col)
		{
			std::string val;
			getline(iss, val, ',');
			
			//if ( !iss.good() )
				//break;

			currentLevelLayout.at(row)[col] = stoi(val);
			
		}
		
	}

	std::ifstream filel(levelPath + levelName + "_logic.csv");

	for (int row = 0; row < height; ++row)
	{
		std::string line;
		getline(filel, line);


		//if ( !file.good() )
		//break;

		std::stringstream iss(line);

		for (int col = 0; col < width; ++col)
		{
			std::string val;
			getline(iss, val, ',');

			//if ( !iss.good() )
			//break;

			currentLevelLayout_l.at(row)[col] = stoi(val);

		}

	}

	std::ifstream fileo(levelPath + levelName + "_objects.csv");

	for (int row = 0; row < height; ++row)
	{
		std::string line;
		getline(fileo, line);


		//if ( !file.good() )
		//break;

		std::stringstream iss(line);

		for (int col = 0; col < width; ++col)
		{
			std::string val;
			getline(iss, val, ',');

			//if ( !iss.good() )
			//break;

			currentLevelLayout_o.at(row)[col] = stoi(val);

		}

	}

	cachedLevelLayouts.push_back(currentLevelLayout);
	cachedLevelLayouts_l.push_back(currentLevelLayout_l);
	cachedLevelLayouts_o.push_back(currentLevelLayout_o);

}


void GameClass::handleEvents(SDL_Event& e)
{
	handleKeyboardEvents();
	handleMouseEvents(e);
	
}

void GameClass::handleMouseEvents(const SDL_Event& e)
{
	if ((e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP))
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		switch (gameState)
		{
		case LAUNCHER:
		{
			launcher->selectedButton = -1;
			launcher->selectedCheck();
			for (int i = 0; i < launcher->buttons.size(); i++)
			{

				Button* b = launcher->buttons.at(i);
				if (b->isInside(x, y))
				{
					launcher->selectedButton = i;
					launcher->selectedCheck();

					if (e.type == SDL_MOUSEBUTTONUP && launcher->selectedButton == i)
					{
						audio_manager->playSoundEffect("ButtonSelected");
						setGameState(launcher->buttons.at(launcher->selectedButton)->getOnClickTransition());
					}
				}
			}
			break;
			}	
		case HELP:
		{
			help->selectedButton = -1;
			help->selectedCheck();
			for (int i = 0; i < help->buttons.size(); i++)
			{

				Button* b = help->buttons.at(i);
				if (b->isInside(x, y))
				{
					help->selectedButton = i;
					help->selectedCheck();

					if (e.type == SDL_MOUSEBUTTONUP && help->selectedButton == i)
					{
						audio_manager->playSoundEffect("ButtonSelected");
						setGameState(help->buttons.at(help->selectedButton)->getOnClickTransition());
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
		case LAUNCHER:
		{
					 if (currentKeyStates[SDL_SCANCODE_UP])
					 {
						 if (launcher->selectedButton > 0) launcher->selectedButton--;
						 launcher->selectedCheck();
					 }
					 else if (currentKeyStates[SDL_SCANCODE_DOWN])
					 {
						 if (launcher->selectedButton < (launcher->buttons.size() - 1)) launcher->selectedButton++;
						 launcher->selectedCheck();
					 }
					 else if (currentKeyStates[SDL_SCANCODE_RETURN])
					 {
						 if (launcher->selectedButton!=-1)
						 {
							 audio_manager->playSoundEffect("ButtonSelected");

							 audio_manager->ManageMusic(STOP, "LauncherTheme");
							 setGameState(launcher->buttons.at(launcher->selectedButton)->getOnClickTransition());
							 audio_manager->ManageMusic(PLAY, "MainTheme", MIX_FADING_IN, 3000);
						 }
					 }
					 break;}
		case GAME:
		{

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
						 //player_->Move(uDlR);
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
						 //player_->Slash(uDlR, true);
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
	centerY = static_cast<int>(actor->position.y + 0.5);
	centerX = static_cast<int>(actor->position.x + 0.5);

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

			actor->currentWorldKnowledge[currentGridCellY][currentGridCellX] = currentLevelLayout_l.at(levelLayoutH - (centerY + j) - 1)[centerX + i];
			currentGridCellX++;
		}
		currentGridCellY++;
	}
	
	//SDL_LogDebug(0, "Finished Setting Object World Knowledge");

	
}


void GameClass::setCamera2D(Camera2D* camera_)
{
	camera = camera_;
	camera->follow(centerDummy);
}


void GameClass::setGameState(GameState gs)
{
	gameState = gs;
	switch (gameState)
	{
	case GAME:
		{

			audio_manager->ManageMusic(STOP, "LauncherTheme");
			audio_manager->ManageMusic(PLAY, "MainTheme", MIX_FADING_IN, 3000);
			camera->follow(player_);
			camera->centerOnObject(player_);
			break;
		}
	default:
	{
		camera->follow(centerDummy);
		break;
	}
	}
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