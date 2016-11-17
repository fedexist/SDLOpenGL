#include "stdafx.h"
#include "DrawingPlane.h"


DrawingPlane::DrawingPlane()
{
}

DrawingPlane::DrawingPlane(GLfloat a[3], GLfloat b[3], GLfloat c[3], GLfloat d[3])
{
	vertices[0][0] = a[0];
	vertices[0][1] = a[1];
	vertices[0][2] = a[2];

	vertices[1][0] = b[0];
	vertices[1][1] = b[1];
	vertices[1][2] = b[2];

	vertices[2][0] = c[0];
	vertices[2][1] = c[1];
	vertices[2][2] = c[2];

	vertices[3][0] = d[0];
	vertices[3][1] = d[1];
	vertices[3][2] = d[2];

	
	color[0] = 0.3f;
	color[1] = 0.2f;
	color[2] = 0.6f;
	color[3] = 1.0f;
}

void DrawingPlane::loadMedia(SDL_Renderer* sdl_renderer)
{
	std::string path = "./assets/not_a_sprite.png";

	tex = LTexture2D(path, 4, 1, sdl_renderer);
}

void DrawingPlane::render()
{
	glBegin(GL_TRIANGLES);
	glColor3fv(color);

	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);
	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
	
	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
	glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);
	glEnd();

	SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Rendering Plane");
}

DrawingPlane::~DrawingPlane()
{
}
