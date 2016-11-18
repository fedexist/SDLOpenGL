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

void DrawingPlane::loadMedia()
{
	std::string path = "./assets/tiles1.png";

	tex = LTexture2D(path, 64, 64);
}

void DrawingPlane::render(std::vector<GLuint*> *levelLayout, unsigned int w, unsigned int h)
{

	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%d %d %d", levelLayout->at(1)[9], w, h );
	
	for (int i = h-1; i == 0; i--)
		for (int j = 0; j < w; j++)

			//tex.drawSprite(2*float(j)/w - 1, 1- 2*float(i)/h, levelLayout->at(i)[j]);
	
	//tex.drawSprite(0, 0, 9);


	/*GLfloat Lvertices[] = {
		 vertices[0][0], vertices[0][1], vertices[0][2] ,
		 vertices[1][0], vertices[1][1], vertices[1][2] ,
		 vertices[2][0], vertices[2][1], vertices[2][2] ,
		 vertices[2][0], vertices[2][1], vertices[2][2] ,
		 vertices[3][0], vertices[3][1], vertices[3][2] ,
		 vertices[0][0], vertices[0][1], vertices[0][2] ,
	};
	
	GLfloat Lcolors[] = {
		color[0], color[1], color[2], color[3],
		color[0], color[1], color[2], color[3],
		color[0], color[1], color[2], color[3],
		color[0], color[1], color[2], color[3],
		color[0], color[1], color[2], color[3],
		color[0], color[1], color[2], color[3],
	};*/
	

}

DrawingPlane::~DrawingPlane()
{
}
