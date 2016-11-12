#pragma once
class DrawingPlane
{
	GLfloat vertices[4][3];
	GLfloat color[4]; 
public:
	DrawingPlane();
	DrawingPlane(GLfloat[3], GLfloat[3], GLfloat[3], GLfloat[3]);
	~DrawingPlane();
	void render();
};

