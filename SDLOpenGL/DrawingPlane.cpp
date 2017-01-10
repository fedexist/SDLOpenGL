#include "stdafx.h"
#include "DrawingPlane.h"


DrawingPlane::DrawingPlane()
{
}

void DrawingPlane::loadMedia()
{
	std::string path = "./assets/DungeonTiles.png";

	tex = LTexture2D(path, 64, 64);
}

void DrawingPlane::render(std::vector<GLuint*> *levelLayout, unsigned int w, unsigned int h)
{
	
	for (int i = 0; i < h; i++) // riga
	{
		for (int j = 0; j < w; j++) //colonna
		{
			tex.drawSprite(j, i, 0, levelLayout->at(h - i - 1)[j]); //drawsprite(x,y, value)

		}
	}	

}

DrawingPlane::~DrawingPlane()
{
}
