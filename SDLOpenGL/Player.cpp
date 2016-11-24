#include "stdafx.h"
#include "Player.h"
#include <numeric>


Player::Player(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, LTexture2D* tex, float mass, unsigned int begInd, unsigned int endInd): 
	GameObject(pos, mom, dim, vis, canInt, tex, mass, begInd, endInd)
{
	lifepoints = 1000.0f;
	damage = 50.0f;
}


Player::~Player()
{
}
