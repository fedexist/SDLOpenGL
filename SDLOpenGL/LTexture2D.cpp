#include "stdafx.h"
#include "LTexture2D.h"


LTexture2D::LTexture2D()
{
}

bool LTexture2D::loadFromFile()
{
	//Get rid of preexisting texture
	free();

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == nullptr )
	{
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGBA( loadedSurface->format, 0, 0, 0, 0 ) );

			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
			texId = 0;
	
			glGenTextures(1, &texId);
			glBindTexture(GL_TEXTURE_2D, texId);

			glGenerateMipmap(GL_TEXTURE_2D);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedSurface->w, loadedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, loadedSurface->pixels);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return true;


}

LTexture2D::LTexture2D(std::string path, unsigned int w_number, unsigned int h_number)
{
	this->path = path;
	w_step = w_number;
	h_step = h_number;
	framePeriod = 0;

	if( loadFromFile())
	{
		for(int i=0; i< height; i += h_step)
		{
			for(int j=0; j<width; j += w_step)
			{
				tile_list.push_back(Tile(j, i));
			}
		}
	}
		
}


LTexture2D::LTexture2D(std::string path, unsigned int w_number, unsigned int h_number, unsigned int framePeriod)
{
	this->path = path;
	w_step = w_number;
	h_step = h_number;
	this->framePeriod = framePeriod;

	if (loadFromFile())
	{
		for (int i = 0; i< height; i += h_step)
		{
			for (int j = 0; j<width; j += w_step)
			{
				tile_list.push_back(Tile(j, i));
			}
		}
	}

}


void LTexture2D::drawSprite(float posX, float posY, float posZ, int frameIndex)
{
	GLfloat Lvertices[] = {
		posX*w_step, posY*h_step, posZ,
		(posX + 1)*w_step, posY*h_step, posZ,
		(posX + 1)*w_step, (posY + 1)*h_step, posZ,
		posX*w_step, (posY + 1)*h_step, posZ
	};
	GLfloat Lcolors[] = {
		1, 1, 1, 1.0,
		1, 1, 1, 1.0,
		1, 1, 1, 1.0,
		1, 1, 1, 1.0,
	};

	const float tx = float(tile_list.at(frameIndex).posX) / width;
	const float ty = float(tile_list.at(frameIndex).posY)/ height +float(h_step)/height;

	
	/*char a[255] = "";
	sprintf_s(a, "%d %f %f", frameIndex, tx, ty);
	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, a);*/
	
	const float tex_verts[] = {
		
		/*0,1,
		0.25,1,
		0.25,0,
		0,0*/
		tx, ty,
		tx + float(w_step) / width, ty,
		tx + float(w_step) / width, 
		ty - float(h_step) /height,
		tx, ty - float(h_step) / height
		

		/*ty, tx + w_step / 64,
		ty + h_step / 128, tx + w_step / 64,
		ty + h_step / 128, tx,
		ty, tx*/
	};
	/*
	std::string str = "";
	for (int i = 0; i < 8; i++)
	{
		str = str + " " + std::to_string(Lvertices[i]) ;
	}
	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, str.c_str());*/
	// activate and specify pointer to vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexCoordPointer(2, GL_FLOAT, 0, tex_verts);
	glVertexPointer(3, GL_FLOAT, 0, Lvertices);
	glColorPointer(4, GL_FLOAT, 0, Lcolors);

	glDrawArrays(GL_QUADS, 0, 4);

	// deactivate vertex arrays after drawing
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	

	
}

void LTexture2D::free()
{
	
}

LTexture2D::~LTexture2D()
{
}
