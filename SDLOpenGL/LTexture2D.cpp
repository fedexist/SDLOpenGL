#include "stdafx.h"
#include "LTexture2D.h"


LTexture2D::LTexture2D()
{
}

bool LTexture2D::loadFromFile(SDL_Renderer* sdl_renderer)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == nullptr )
	{
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
		
		newTexture = SDL_CreateTextureFromSurface(sdl_renderer, loadedSurface );
		if( newTexture == nullptr )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	tex = newTexture;
	return tex != nullptr;


}

LTexture2D::LTexture2D(std::string path, unsigned int w_number, unsigned int h_number, SDL_Renderer* sdl_renderer)
{
	this->path = path;
	w_step = w_number;
	h_step = h_number;
	tex = nullptr;

	if( loadFromFile(sdl_renderer))
	{
		for(int i=0; i< height; i += h_step)
		{
			for(int j=0; j<width; j += w_step)
			{
				tile_list.push_back(Tile(i, j));
			}
		}
	}

	
		
}

void LTexture2D::drawSprite(float posX, float posY, int frameIndex)
{

	/*
	glVertexPointer(2, GL_FLOAT, verts);
	glTexCoordPointer(2, GL_FLOAT, texVerts);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);*/
}

void LTexture2D::free()
{
	if (tex != nullptr)
	{
		SDL_DestroyTexture(tex);
		tex = nullptr;
		width = 0;
		height = 0;
	}
}

LTexture2D::~LTexture2D()
{
}