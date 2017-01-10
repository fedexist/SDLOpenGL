#include "stdafx.h"
#include "Button.h"
#include "GameClass.h"

Button::Button(){};

Button::Button(glm::vec2 pos, glm::vec2 dim, LTexture2D* tex, GameState onClick, Text* t)
{
	positionRel = pos;
	texture = tex;
	onClickStateTransition = onClick;
	dimensions = dim;
	text = t;
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
	text->drawText((positionRel.x+0.5)*(dimensions.x / text->textDimensions.x) - 0.50,
				   (positionRel.y+0.5)*(dimensions.y / text->textDimensions.y) - 0.55);
}

Button::~Button() {}


