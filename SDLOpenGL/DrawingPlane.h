#pragma once
#include "LTexture2D.h"

class DrawingPlane
{
	GLfloat vertices[4][3];
	GLfloat color[4];
	LTexture2D tex;
	
public:
	DrawingPlane();
	DrawingPlane(GLfloat[3], GLfloat[3], GLfloat[3], GLfloat[3]);
	void loadMedia(SDL_Renderer * sdl_renderer);	
	~DrawingPlane();
	void render();
};

