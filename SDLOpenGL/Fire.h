#pragma once
#include "GameObject.h"
class Fire :
	public GameObject
{
public:
	/**
  @param position_ GameObject starting position
  @param momentum_ GameObject momentum
  @param dimensions_ glm::vec2 containing the object dimensions
  @param visible_ is it visible?
  @param texture LTexture2D* pointing to the spritesheet this GameObject belongs
  @param mass GameObject mass for the physics system
  @param beginIndex This is the starting index of the GameObject animation
  @param endingIndex This is the ending index of the GameObject animation
  @param am AudioManager* pointing to the Core's AudioManager, needed when a GameObject need to play a sound effect  
*/
	Fire(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, LTexture2D* tex, float mass, unsigned int begInd, unsigned int endInd);
	Fire(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, float mass, Fire* other);
	void update(float dt);
	~Fire();
private:
	void onInteraction();
};

