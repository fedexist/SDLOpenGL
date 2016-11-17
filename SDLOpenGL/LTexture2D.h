#pragma once
#include "stdafx.h"

class Tile
{
public:
	GLuint textureId;

};

class LTexture2D
{
	std::string path;
	SDL_Texture* tex;
	unsigned int width;
	unsigned int height;
	unsigned int w_step, h_step;

	std::vector<Tile> tile_list;
public:
	LTexture2D();
	bool loadFromFile(SDL_Renderer * sdl_renderer);
	LTexture2D(std::string path, unsigned int w_number, unsigned int h_number, SDL_Renderer * sdl_renderer);
	void drawSpritesheet();
	void free();
	~LTexture2D();
};

