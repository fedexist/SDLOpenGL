#include "stdafx.h"
#include "GameClass.h"
#include <fstream>
#include "Player.h"


GameClass::GameClass()
{
	GLfloat p1[] = { -0.0f, 1.0f, 0.0f };
	GLfloat p2[] = { 1.0f, 1.0f, 0.0f };
	GLfloat p3[] = { 1.0f, -1.0f, 0.0f };
	GLfloat p4[] = { -1.0f, -1.0f, 0.0f };
	plane = DrawingPlane(p1, p2, p3, p4);
	cachedLevelLayouts = std::vector< std::vector<GLuint*> >();
	gameObjectArray = std::vector<GameObject*>();
	allObjectsFactory = std::vector<GameObject*>();
	allTextures = std::vector<LTexture2D>();
	gameState = LAUNCHER;
}


GameClass::~GameClass()
{

}


void GameClass::update(float dt)
{
	setObjectWorldKnowledge(player_); //dovrebbe essere fatto per ogni actor
	for (int i = 0; i < gameObjectArray.size();i++)
	{
		gameObjectArray.at(i)->update(dt);
	}
	player_->update(dt);
	camera->update(dt);
	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "I'm in the update function of GameClass, current delta is: %f\n", dt);
	
	//SDL_Delay(1);
}

void GameClass::loadMedia()
{
	//AllGameResources.loadMedia(sdl_renderer)
	plane.loadMedia();
	launcher = new Launcher();

	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "About to loadLevelLayout()\n");
	loadLevelLayout("room1", 10, 10);

	//Caricamento textures
	allTextures.push_back(LTexture2D("./assets/CampFireFinished.png",64,64,10));
	allTextures.push_back(LTexture2D("./assets/player.png", 64, 64, 5));

	allObjectsFactory.push_back(new GameObject(glm::vec2(0.0, 0.0), glm::vec2(0, 0), glm::vec2(64, 64), true, true, &allTextures.at(0), 0.05, 0, 4));
	allObjectsFactory.push_back(new Player(glm::vec2(4.5, 4.5), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, &allTextures.at(1), 1, 26, 28));
	
	for (int j = 0; j < levelLayoutH; j++)
	{
		for (int i = 0; i < levelLayoutW; i++)
		{
			int objectIndex = currentLevelLayout_o.at(j)[i];
			if (objectIndex > -1)
			{
				gameObjectArray.push_back(new GameObject(glm::vec2(i,(levelLayoutH - j-1)), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, 1.0, allObjectsFactory.at(objectIndex)));
			}
		}
	}
	
	player_ = new Player(glm::vec2(4.5, 4.5), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, &allTextures.at(1), 1, 26, 28);
	gameObjectArray.push_back(player_);

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
	case GAME:
		plane.render(&currentLevelLayout, levelLayoutW, levelLayoutH);
		sort(gameObjectArray.begin(), gameObjectArray.end(), gameObjectArray.at(0)->gameObjectComparer);
		for (int i = 0; i < gameObjectArray.size(); i++)
		{
			if (gameObjectArray.at(i)->isPlayer)
				player_->render();
			else
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
		

	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Initialised currentlevellayout");



	std::ifstream file(levelPath + levelName + ".csv");

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

	std::ifstream filel(levelPath + levelName + "_l.csv");

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

	std::ifstream fileo(levelPath + levelName + "_o.csv");

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
	if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		
		for (int i = 0; i < launcher->buttons.size(); i++)
		{
			Button* b = launcher->buttons.at(i);
			if (b->isInside(x,y))
			{
				launcher->selectedButton = i;
				launcher->selectedCheck();

				if (e.type == SDL_MOUSEBUTTONUP && launcher->selectedButton == i)
				{
					audio_manager->playSoundEffect("ButtonSelected");

					Mix_HaltMusic();

					setGameState(launcher->buttons.at(launcher->selectedButton)->getOnClickTransition());
					audio_manager->ManageMusic(PLAY, "MainTheme", MIX_FADING_IN, 3000);
				}
			}

			else
			{
				launcher->selectedButton = -1;
				launcher->selectedCheck();
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
					 setGameState(launcher->buttons.at(launcher->selectedButton)->getOnClickTransition());
				 }
				 break;}
	case GAME:
	{
				 bool isMoving = currentKeyStates[SDL_SCANCODE_W] || currentKeyStates[SDL_SCANCODE_A] || currentKeyStates[SDL_SCANCODE_S] || currentKeyStates[SDL_SCANCODE_D];
				 bool isSlashing = player_->coolDown == 0 && (currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_RIGHT]);

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
						 player_->coolDown = 40;
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
					 player_->coolDown = 40;
					 player_->Act(SLASHING, uDlR);
					 audio_manager->playSoundEffect("SwordSwish");
				 }
				 if (!(isMoving || isSlashing))
				 {
					 player_->Act(IDLE, glm::vec2(-1, -1));
				 }
				 break;}
	default:
	{
			   break;}
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
	camera->follow(player_);
}


void GameClass::setGameState(GameState gs)
{
	gameState = gs;
}

void GameClass::setAudioManager(AudioManager* audio_manager)
{
	this->audio_manager = audio_manager;
}
