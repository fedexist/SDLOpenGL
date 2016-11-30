#include "stdafx.h"
#include "GameClass.h"
#include <fstream>
#include "Player.h"


GameClass::GameClass()
{
	GLfloat p1[] = { -1.0f, 1.0f, 0.0f };
	GLfloat p2[] = { 1.0f, 1.0f, 0.0f };
	GLfloat p3[] = { 1.0f, -1.0f, 0.0f };
	GLfloat p4[] = { -1.0f, -1.0f, 0.0f };
	plane = DrawingPlane(p1, p2, p3, p4);
	cachedLevelLayouts = std::vector< std::vector<GLuint*> >();
	gameObjectArray = std::vector<GameObject*>();
	allObjectsFactory = std::vector<GameObject*>();
}


GameClass::~GameClass()
{

}


void GameClass::update(float dt)
{
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
	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "About to loadLevelLayout()\n");

	loadLevelLayout("room1", 10, 10);

	allTextures = std::vector<LTexture2D>();
	allTextures.push_back(LTexture2D("./assets/CampFireFinished.png",64,64,10));
	allTextures.push_back(LTexture2D("./assets/player.png", 64, 64, 5));

	allObjectsFactory.push_back(new GameObject(glm::vec2(0.0, 0.0), glm::vec2(0, 0), glm::vec2(64, 64), true, true, &allTextures.at(0), 0.05, 0, 4));
	
	
	for (int j = 0; j < levelLayoutH; j++)
	{
		for (int i = 0; i < leveLayoutW; i++)
		{
			int objectIndex = currentLevelLayout_o.at(j)[i];
			if (objectIndex > -1)
			{
				gameObjectArray.push_back(new GameObject(glm::vec2(i,(levelLayoutH - j-1)), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, 1.0, allObjectsFactory.at(objectIndex)));
			}
		}
	}
	
	player_ = new Player(glm::vec2(4.5, 4.5), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, &allTextures.at(1), 1, 26, 28);
	gameObjectArray.push_back(player_); }

void GameClass::render()
{
	plane.render(&currentLevelLayout, leveLayoutW, levelLayoutH);
	std::sort(gameObjectArray.begin(), gameObjectArray.end(), gameObjectArray.at(0)->gameObjectComparer);
	for (int i = 0; i < gameObjectArray.size(); i++)
	{
		if (gameObjectArray.at(i)->isPlayer)
			player_->render();
		else
			gameObjectArray.at(i)->render();
	}

}

void GameClass::loadLevelLayout(std::string levelName, unsigned int width, unsigned int height)
{
	currentLevelLayout.clear();
	currentLevelLayout_l.clear();
	currentLevelLayout_o.clear();

	leveLayoutW = width;
	levelLayoutH = height;

	for (int i = 0; i < height; ++i)
	{
		currentLevelLayout.push_back(new GLuint[width]);
		currentLevelLayout_l.push_back(new GLuint[width]);
		currentLevelLayout_o.push_back(new GLuint[width]);
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

void GameClass::handleMouseEvents(const SDL_Event& sdl_event)
{
}

void GameClass::handleEvents(SDL_Event& e)
{
	handleKeyboardEvents();
	
}

void GameClass::handleKeyboardEvents()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

	bool isMoving = currentKeyStates[SDL_SCANCODE_W] || currentKeyStates[SDL_SCANCODE_A] || currentKeyStates[SDL_SCANCODE_S] || currentKeyStates[SDL_SCANCODE_D];
	bool isSlashing = currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_RIGHT];

	if(isMoving)
	{
		glm::vec2 uDlR = glm::vec2(-1, -1);
		if( currentKeyStates[SDL_SCANCODE_W] )
		{
			uDlR.y = UP;
		}
		else if(currentKeyStates[SDL_SCANCODE_S])
		{
			uDlR.y = DOWN;
		}
		if(currentKeyStates[SDL_SCANCODE_A])
		{
			uDlR.x = LEFT;
		} 
		else if (currentKeyStates[SDL_SCANCODE_D]) 
		{
			uDlR.x = RIGHT;
		}
		//player_->Move(uDlR);
		if(isSlashing)
			player_->Act(MOVING_SLASHING, uDlR);
		else 
			player_->Act(MOVING, uDlR);
	}
	else if(isSlashing)
	{
		glm::vec2 uDlR = glm::vec2(-1, -1);
		if( currentKeyStates[SDL_SCANCODE_UP] )
		{
			uDlR.y = UP;
		}
		else if(currentKeyStates[SDL_SCANCODE_DOWN])
		{
			uDlR.y = DOWN;
		}
		if(currentKeyStates[SDL_SCANCODE_LEFT])
		{
			uDlR.x = LEFT;
		} 
		else if (currentKeyStates[SDL_SCANCODE_RIGHT]) 
		{
			uDlR.x = RIGHT;
		}
		//player_->Slash(uDlR, true);
		
		if (isMoving)
			player_->Act(MOVING_SLASHING, uDlR);
		else
			player_->Act(SLASHING, uDlR);

	}

	if(!(isMoving || isSlashing))
	{
		player_->Act(IDLE, glm::vec2(-1,-1));
	}
		
}

void GameClass::setCamera2D(Camera2D* camera_)
{
	camera = camera_;
	camera->follow(player_);
}
