#pragma once
#include "GameObject.h"

class Portal :
	public GameObject
{

public:
	Portal(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, LTexture2D* tex, float mass, unsigned int begInd, unsigned int endInd, AudioManager *am);
	Portal(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, float mass, Portal* other);
	Portal* UpLeft;
	Portal* Next;
	void update(float dt);
	~Portal();
private:
	void onInteraction();
	bool open = false;
};

