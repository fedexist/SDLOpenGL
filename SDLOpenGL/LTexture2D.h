#pragma once
#include "stdafx.h"

class Tile
{
public:
	Tile(GLuint x, GLuint y) : posX(x), posY(y) {}
	GLuint posX;
	GLuint posY;

};

class LTexture2D
{
	std::string path;
	GLuint texId;
	float width;
	float height;
	unsigned int w_step, h_step;

	std::vector<Tile> tile_list;
public:
	unsigned int framePeriod;
	LTexture2D();
	bool loadFromFile();
	LTexture2D(std::string path, unsigned int w_number, unsigned int h_number);
	LTexture2D(std::string path, unsigned int w_number, unsigned int h_number,unsigned int framePeriod);
	void drawSprite(float posX, float posY, float posz, int frameIndex);
	void free();
	~LTexture2D();
};

