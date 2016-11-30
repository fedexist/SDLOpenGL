#pragma once
#include "LTexture2D.h"

class GameObject{
	friend class GameObjectComparer;
	glm::vec2 position;
	glm::vec2 momentum;
	glm::vec2 dimensions;
	glm::vec2 lastTranslation; //traslazione in coordinate griglia
	bool visible;
	bool canInteractWith;
	
	float mass;
public:
	GameObject(glm::vec2 position_, glm::vec2 momentum_, glm::vec2 dimensions_, bool visible_, bool interactable, LTexture2D* texture, float mass, unsigned int beginIndex, unsigned int endingIndex);
	GameObject(glm::vec2 position_, glm::vec2 momentum_, glm::vec2 dimensions_, bool visible_, bool interactable, float mass, GameObject *factory);
	~GameObject();
	void render();
	void update(float dt);
	bool isPlayer = false;
	class GameObjectComparer
	{
		friend class GameObject;
	public:
		GameObjectComparer(){};
		bool operator() (GameObject *i, GameObject *j) {
			return (i->position.y > j->position.y);
		}
	} gameObjectComparer;

	glm::vec2 gridPositionToWorld() const { return glm::vec2( position.x * dimensions.x + dimensions.x / 2, position.y * dimensions.y + dimensions.y / 2 ); }
	glm::vec2 getLastTranslation() const { return glm::vec2( lastTranslation.x * dimensions.x, lastTranslation.y * dimensions.y); } //traslazione in coordinate mondo

protected:
	unsigned int curIndexFrame;
	unsigned int startingIndexFrame;
	unsigned int endingIndexFrame;
	unsigned int framePeriodIndex;
	LTexture2D* tex;
	void handleMovement(float dt, glm::vec2 forceInput);
	void handleAnims(float dt);
	

};

