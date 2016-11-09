#include "stdafx.h"
#include "GameClass.h"


GameClass::GameClass()
{
}


GameClass::~GameClass()
{
}

void GameClass::update(float dt)
{
	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "I'm in the update function of GameClass, current delta is: %f\n", dt);
}
