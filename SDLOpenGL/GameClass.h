#pragma once
#include "GameObject.h"
#include "DrawingPlane.h"

class GameClass
{
	std::vector<GameObject> gameObjectArray;
	DrawingPlane plane;

public:
	GameClass();
	~GameClass();
	static void update(float);
	void loadMedia(SDL_Renderer*);
	void render();
};

