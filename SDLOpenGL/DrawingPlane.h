#pragma once
#include "LTexture2D.h"

class DrawingPlane
{
	GLfloat vertices[4][3];
	GLfloat color[4];
	LTexture2D tex;
	
public:
	DrawingPlane();
	void loadMedia();	
	~DrawingPlane();
	void render(std::vector<GLuint*>*, unsigned int, unsigned int);
};

