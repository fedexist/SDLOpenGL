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
	bool loadFromFile();
	LTexture2D(std::string, unsigned int, unsigned int);
	void drawSpritesheet();
	void free();
	~LTexture2D();
};

