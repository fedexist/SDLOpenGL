#include "stdafx.h"
#include "Background.h"


Background::Background(std::string path, int w, int h)
{
	backgroundDim = glm::vec2(w, h);
	backgroundTexture = new LTexture2D("./assets/background_launcher.png", backgroundDim.x, backgroundDim.y);
}

void Background::render()
{
	backgroundTexture->drawSprite(0, 0, -1, 0);
}

glm::vec2 Background::getBackgroundDim()
{
	return backgroundDim;
}

Background::~Background()
{
}
