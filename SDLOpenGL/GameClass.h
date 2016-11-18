#pragma once
#include "GameObject.h"
#include "DrawingPlane.h"

class GameClass
{
	std::vector<GameObject> gameObjectArray;
	DrawingPlane plane;
	std::vector<GLuint*> currentLevelLayout;
	std::string levelPath = "./assets/levels/";
	std::vector< std::vector<GLuint*> > cachedLevelLayouts;

public:
	GameClass();
	~GameClass();
	static void update(float);
	void loadMedia();
	void render();
	void loadLevelLayout(std::string, unsigned int, unsigned int);
	std::vector<GLuint*> getLevelLayout() const { return currentLevelLayout; } //probabilmente non necessaria

};

