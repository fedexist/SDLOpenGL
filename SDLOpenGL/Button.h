#pragma once
#include "GameClass.h"

typedef enum LButtonSprite
{
	BUTTON_SPRITE_OUT,
	BUTTON_SPRITE_OVER_MOTION,

}LButtonSprite;

class Button
{
public:
	Button();
	Button(glm::vec2 pos, glm::vec2 dim, LTexture2D* tex, enum GameState onClickStateTransition);
	~Button();

	bool isInside(int x, int y);
	void setCurSprite(enum LButtonSprite sprite);
	GameState getOnClickTransition();
	void render();

private:
	LTexture2D* texture;
	enum LButtonSprite curSprite;
	enum GameState onClickStateTransition;
	glm::vec2 positionRel;
	glm::vec2 positionPx;
	glm::vec2 dimensions;
	
};
