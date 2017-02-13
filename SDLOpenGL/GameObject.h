#pragma once
#include "LTexture2D.h"
#include "AudioManager.h"

class GameObject{

	friend class GameObjectComparer;
	friend class GameClass;

	
	glm::vec2 momentum;
	glm::vec2 dimensions; //dimensione della sola sprite
	glm::vec2 lastTranslation; //traslazione in coordinate griglia
	bool canInteractWith;

	float mass;

	std::vector< GLint* > currentWorldKnowledge;
	
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
	GameObject(glm::vec2 position_, glm::vec2 momentum_, glm::vec2 dimensions_, bool visible_, bool interactable, LTexture2D* texture, float mass, unsigned int beginIndex, unsigned int endingIndex, AudioManager* am);
	GameObject(glm::vec2 position_, glm::vec2 momentum_, glm::vec2 dimensions_, bool visible_, bool interactable, float mass, GameObject *factory);
	//GameObject();
	virtual ~GameObject();
	void render();
	virtual void update(float dt)=0;
	bool isPlayer = false;
	GameObject* attachedTo = nullptr;
	
	bool visible;

	class GameObjectComparer
	{
		friend class GameObject;
	public:
		GameObjectComparer(){};
		bool operator() (GameObject *i, GameObject *j) {
			float ivalue, jvalue;
			if (i->attachedTo == nullptr)
				ivalue = i->position.y;
			else
				ivalue = i->attachedTo->position.y;

			if (j->attachedTo == nullptr)
				jvalue = j->position.y;
			else
				jvalue = j->attachedTo->position.y;

			return (ivalue > jvalue);
		}
	} gameObjectComparer;

	//utility functions
	glm::vec2 gridPositionToWorld() const { return glm::vec2( position.x * dimensions.x + dimensions.x / 2, position.y * dimensions.y + dimensions.y / 2 ); }
	glm::vec2 spriteCenter() const { return glm::vec2(position.x + 0.5, position.y + 0.5); }
	glm::vec2 currentCell() const { return glm::vec2(floorf(position.x + 0.5), floorf(position.y + 0.5)); }
	glm::vec2 getLastTranslation() const { return glm::vec2( lastTranslation.x * dimensions.x, lastTranslation.y * dimensions.y); } //traslazione in coordinate mondo
	bool isHitboxInsideCell(glm::vec2 cell);
	void resizeHitBox(glm::vec2 resize) { hitboxDimensions = glm::vec2(hitboxDimensions.x*resize.x,hitboxDimensions.y*resize.y); };

	bool isWalkable(glm::vec2 candidateTranslation);
	virtual void getHit(float hitNumber, GameObject* hitter)
	{
	};

protected:
	unsigned int curIndexFrame;
	unsigned int startingIndexFrame;
	unsigned int endingIndexFrame;
	unsigned int framePeriodIndex;

	AudioManager* audio_manager;
	
	glm::vec2 position; //Il centro della sprite è Position + vec2(0.5)

	glm::vec2 hitboxDimensions = glm::vec2(30.f/64.f, 31.f/64.f); //dimensione della hitbox rispetto al centro della sprite p.e. per una 64x64 -> (15,20), cioè una hitbox 30x40, con centro position + vec(0.5)

	std::vector<GameObject*> areaSharing;
	LTexture2D* tex;
	void handleAnims(float dt);
	void handleMovement(float dt, glm::vec2 forceInput);
	

};

