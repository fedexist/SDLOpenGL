#pragma once
#include "stdafx.h"


class Text
{
	TTF_Font* font;
	std::string fontPath;
	std::string message;
	SDL_Color color;
	int pointSize;
	SDL_Surface* surface;
	GLuint textureID;	

public:
	Text() {};
	~Text();
	Text(TTF_Font* font_, std::string m, SDL_Color c, int size);
	bool loadFont();
	void drawText(float posX, float posY);
	void free();
	glm::vec2 textDimensions;
};

