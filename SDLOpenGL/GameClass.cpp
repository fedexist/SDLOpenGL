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
	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "I'm in the update function of GameClass, current delta is: %f\n", dt);
	
	//SDL_Delay(1);
}

void GameClass::loadMedia()
{
	//AllGameResources.loadMedia(sdl_renderer)
	plane.loadMedia();
	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "About to loadLevelLayout()\n");
	loadLevelLayout("room1.csv", 10, 10);
	allTextures = std::vector<LTexture2D>();

	allTextures.push_back(LTexture2D("./assets/CampFireFinished.png",64,64,10));
	allTextures.push_back(LTexture2D("./assets/player.png", 64, 64, 8));

	gameObjectArray.push_back(new GameObject(glm::vec2(0.5, 0.5), glm::vec2(0.0, 0.0), glm::vec2(64, 64), true, true, &allTextures.at(0), 1, 0, 4));
	gameObjectArray.push_back(new Player(glm::vec2(9.5, 9.5), glm::vec2(0.2, 0.2), glm::vec2(64, 64), true, true, &allTextures.at(0), 1, 0, 4));
}

void GameClass::render()
{
	plane.render(&currentLevelLayout, leveLayoutW, levelLayoutH);
	for (int i = 0; i < gameObjectArray.size(); i++)
	{
		gameObjectArray.at(i)->render();
	}
}

void GameClass::loadLevelLayout(std::string levelName, unsigned int width, unsigned int height)
{

	currentLevelLayout.clear();

	leveLayoutW = width;
	levelLayoutH = height;

	for (int i = 0; i < height; ++i)
		currentLevelLayout.push_back(new GLuint[width]);

	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Initialised currentlevellayout");



	std::ifstream file(levelPath + levelName);

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

	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Tiles (0,0) (0,1) (0,2) (0,3): %d %d %d %d\n", currentLevelLayout.at(0)[0], currentLevelLayout.at(0)[1], currentLevelLayout.at(0)[2], currentLevelLayout.at(0)[3]);

	cachedLevelLayouts.push_back(currentLevelLayout);

}
