#include "stdafx.h"
#include "Button.h"
#include "GameClass.h"

Button::Button(){};

Button::Button(glm::vec2 pos, glm::vec2 dim, LTexture2D* tex, GameState onClick)
{
	position = pos;
	dimensions = dim;
	texture = tex;
	onClickStateTransition = onClick;
}

bool Button::isInside(int x, int y)
{
	bool inside = true;
	if (x < position.x || x > position.x + dimensions.x || y < position.y || y > position.y + dimensions.y)
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
	texture->drawSprite(position.x, position.y, 1, curSprite);
}

Button::~Button() {}
