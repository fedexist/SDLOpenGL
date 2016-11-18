#include "stdafx.h"
#include "GameClass.h"
#include <fstream>


GameClass::GameClass()
{
	GLfloat p1[] = { -1.0f, 1.0f, 0.0f };
	GLfloat p2[] = { 1.0f, 1.0f, 0.0f };
	GLfloat p3[] = { 1.0f, -1.0f, 0.0f };
	GLfloat p4[] = { -1.0f, -1.0f, 0.0f };
	plane = DrawingPlane(p1, p2, p3, p4);
	cachedLevelLayouts = std::vector< std::vector<GLuint*> >();
}


GameClass::~GameClass()
{

}

void GameClass::update(float dt)
{
	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "I'm in the update function of GameClass, current delta is: %f\n", dt);
}

void GameClass::loadMedia()
{
	//AllGameResources.loadMedia(sdl_renderer)
	plane.loadMedia();
	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "About to loadLevelLayout()\n");
	loadLevelLayout("room1.csv", 10, 10);
}

void GameClass::render()
{
	plane.render();
}

void GameClass::loadLevelLayout(std::string levelName, unsigned int width, unsigned int height)
{

	currentLevelLayout.clear();


	for (int i = 0; i < height; ++i)
		currentLevelLayout.push_back(new GLuint[width]);

	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Initialised currentlevellayout");



	std::ifstream file(levelPath + levelName);

	for(int row = 0; row < height; ++row)
	{
		std::string line;
		getline(file, line);
		if ( !file.good() )
			break;

		std::stringstream iss(line);

		for (int col = 0; col < width; ++col)
		{
			std::string val;
			getline(iss, val, ',');
			if ( !iss.good() )
				break;

			currentLevelLayout.at(row)[col] = stoi(val);
		}
	}

	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Tiles (0,0) (0,1) (0,2) (0,3): %d %d %d %d\n", currentLevelLayout.at(0)[0], currentLevelLayout.at(0)[1], currentLevelLayout.at(0)[2], currentLevelLayout.at(0)[3]);

	cachedLevelLayouts.push_back(currentLevelLayout);

}
