#include "stdafx.h"
#include "DrawingPlane.h"


DrawingPlane::DrawingPlane()
{
}

DrawingPlane::DrawingPlane(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* d)
{
	//vertices = std::vector<GLfloat*>(4);
	vertices = new GLfloat*();
	vertices[0] = a;
	vertices[1] = b;
	vertices[2] = c;
	vertices[3] = d;
	color[0] = 0.3f;
	color[1] = 0.2f;
	color[2] = 0.6f;
	color[3] = 1.0f;
}

void DrawingPlane::render()
{
	glBegin(GL_TRIANGLES);
	glColor3fv(color);

	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);
	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
	/*glVertex3f(vertices[1]);
	glVertex3f(vertices[2]);
	glVertex3f(vertices[2]);
	glVertex3f(vertices[3]);
	glVertex3f(vertices[1]);*/
	glEnd();

	SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Rendering Plane");
}

DrawingPlane::~DrawingPlane()
{
}
