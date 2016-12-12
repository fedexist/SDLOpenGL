#pragma once
#include "LTexture2D.h"

class GameObject{

	friend class GameObjectComparer;
	friend class GameClass;

	
	glm::vec2 momentum;
	glm::vec2 dimensions; //dimensione della sola sprite
	glm::vec2 lastTranslation; //traslazione in coordinate griglia
	bool visible;
	bool canInteractWith;
	
	float mass;

	std::vector< GLint* > currentWorldKnowledge;
	
public:
	GameObject(glm::vec2 position_, glm::vec2 momentum_, glm::vec2 dimensions_, bool visible_, bool interactable, LTexture2D* texture, float mass, unsigned int beginIndex, unsigned int endingIndex);
	GameObject(glm::vec2 position_, glm::vec2 momentum_, glm::vec2 dimensions_, bool visible_, bool interactable, float mass, GameObject *factory);
	//GameObject();
	~GameObject();
	void render();
	virtual void update(float dt);
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
	glm::vec2 spriteCenter() const { return glm::vec2(position.x + 0.5, position.y + 0.5); }
	glm::vec2 getLastTranslation() const { return glm::vec2( lastTranslation.x * dimensions.x, lastTranslation.y * dimensions.y); } //traslazione in coordinate mondo
	bool isWalkable(glm::vec2 candidateTranslation);
	virtual void getHit(float hitNumber, GameObject* hitter)
	{
	};

protected:
	unsigned int curIndexFrame;
	unsigned int startingIndexFrame;
	unsigned int endingIndexFrame;
	unsigned int framePeriodIndex;

	glm::vec2 position; //Il centro della sprite è Position + vec2(0.5)

	glm::vec2 hitboxDimensions = glm::vec2(17.f/64.f, 30.f/64.f); //dimensione della hitbox rispetto al centro della sprite p.e. per una 64x64 -> (15,20), cioè una hitbox 30x40, con centro position + vec(0.5)

	std::vector<GameObject*> areaSharing;
	LTexture2D* tex;
	void handleAnims(float dt);
	void handleMovement(float dt, glm::vec2 forceInput);
	

};

