#include "stdafx.h"
#include "Button.h"
#include "GameClass.h"

Button::Button(){};

Button::Button(glm::vec2 pos, glm::vec2 dim, LTexture2D* tex, GameState onClick)
{
	positionRel = pos;
	texture = tex;
	onClickStateTransition = onClick;
	dimensions = dim;
	positionPx = glm::vec2(((1280 - 640) / 2) + pos.x*dim.x, ((720 - 640) / 2) + 640 - pos.y*dim.y); // (0,0) in alto a sx
}

bool Button::isInside(int x, int y)
{
	bool inside = true;
	if (x < positionPx.x || x > positionPx.x + dimensions.x || y > positionPx.y || y < positionPx.y - dimensions.y)
	{
		inside = false;
	}
	return inside;
}

void Button::setCurSprite(enum LButtonSprite sprite)
{
	curSprite = sprite;
}

GameState Button::getOnClickTransition()
{
	return onClickStateTransition;
}

void Button::render()
{
	texture->drawSprite(positionRel.x, positionRel.y, 0, curSprite);
}

Button::~Button() {}
