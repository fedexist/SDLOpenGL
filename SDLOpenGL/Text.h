#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

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
	Text(std::string path, std::string message, SDL_Color, int ptSize);
	~Text();
	bool loadFont();
	void drawText(float posX, float posY);
	void free();
	glm::vec2 textDimensions;
};

