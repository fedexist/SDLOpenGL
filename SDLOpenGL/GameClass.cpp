#include "stdafx.h"
#include "GameClass.h"


GameClass::GameClass()
{
	GLfloat p1[] = { -1.0f, 1.0f, 0.0f };
	GLfloat p2[] = { 1.0f, 1.0f, 0.0f };
	GLfloat p3[] = { 1.0f, -1.0f, 0.0f };
	GLfloat p4[] = { -1.0f, -1.0f, 0.0f };
	plane = DrawingPlane(p1, p2, p3, p4);
}


GameClass::~GameClass()
{
}

void GameClass::update(float dt)
{
	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "I'm in the update function of GameClass, current delta is: %f\n", dt);
}

void GameClass::render()
{
	plane.render();
}
