#pragma once
class DrawingPlane
{
	GLfloat** vertices;
	GLfloat color[4]; 
public:
	DrawingPlane();
	DrawingPlane(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* d);
	~DrawingPlane();
	void render();
};

