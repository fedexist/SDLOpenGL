#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject(glm::vec2 position_, glm::vec2 momentum_, glm::vec2 dimensions_, bool visible_, bool interactable, LTexture2D* texture, float mass, unsigned int beginIndex, unsigned int endingIndex)
{
	position = position_;
	momentum = momentum_;
	dimensions = dimensions_;
	visible = visible_;
	canInteractWith = interactable;
	this->tex = texture;
	curIndexFrame = beginIndex;
	startingIndexFrame = beginIndex;
	endingIndexFrame = endingIndex;
	framePeriodIndex = tex->framePeriod;
	this->mass = mass;
}

void GameObject::render()
{
	tex->drawSprite(position.x, position.y, 1, curIndexFrame);
}

void GameObject::update(float dt)
{

	if ((--framePeriodIndex) == 0)
	{
		framePeriodIndex = tex->framePeriod;
		curIndexFrame -= startingIndexFrame;
		curIndexFrame = (curIndexFrame + 1) % (endingIndexFrame - startingIndexFrame);
		curIndexFrame += startingIndexFrame;
	}
	
	//movement
	
	float alpha, Fa, mu, Fas; //alpha è la forza per ogni tick in cui è premuto il tasto, 
	//Fa è la forza di attrito
	//mu è la costante di attrito
	//Fas è la forza di attrito statico
	alpha = 5;
	mu = 0.1;
	Fa = 0.0001 * mu * 9.81 * mass;
	Fas = glm::min<float>(1.2* mu * mass, alpha); //ragionevole

	glm::vec2 oldMomentum = momentum;
	glm::vec2 oldVelocity = oldMomentum / mass;
	glm::vec2 forceInput = glm::vec2(0.0, 0.0);
	glm::vec2 forceStaticResistance = glm::vec2(0,0);
	
	/*
	 *Lo static cast potrebbe non essere la soluzione ideale
	 *
	Player* pg = static_cast<Player*>(this);		
	
	if(pg != nullptr)
	{
		if ( pg->isMoving(UP))
		{
			forceInput.y = 1.0f;
		}
		else if (pg->isMoving(DOWN))
		{
			//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "S is pressed");
			forceInput.y = -1.0f;
		}
		if (pg->isMoving(RIGHT))
		{
			//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "D is pressed");
			forceInput.x = 1.0f;
		}
		else if (pg->isMoving(LEFT))
		{
			//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "A is pressed");
			forceInput.x = -1.0f;
		}
	}*/


	if( dot(forceInput,forceInput) > 0)
		forceInput = normalize(forceInput);
	

	if (oldVelocity.x > -0.1 && oldVelocity.x < 0.1)
		forceStaticResistance.x = -Fas * forceInput.x;

	if (oldVelocity.y > -0.1 && oldVelocity.y < 0.1)
		forceStaticResistance.y = -Fas * forceInput.y;


	glm::vec2 direction = oldMomentum;
	
	//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "direction %f %f",direction.x,direction.y);

	if (dot(direction,direction)> 0)
		direction = normalize(direction);
	
	glm::vec2 force = alpha * forceInput - Fa * direction + forceStaticResistance; //la forza totale è quella di input meno la viscosità

	//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "force %f %f", force.x, force.y);

	momentum = oldMomentum + force;

	glm::vec2 vel = momentum / mass;

	if (oldVelocity.y * vel.y < 0)
	{
		vel.y = 0;
		momentum.y = 0;
	}
	if (oldVelocity.x * vel.x < 0)
	{
		vel.x = 0;
		momentum.x = 0;
	}	


	position += vel * dt; //calcolo spostamento dalla velocità

}


GameObject::~GameObject()
{
}
