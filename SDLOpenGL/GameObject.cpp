#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject(glm::vec2 pos, glm::vec2 mom, glm::vec2 dim, bool vis, bool canInt, LTexture2D* tex, float mass, unsigned int begInd, unsigned int endInd)
{
	position = pos;
	momentum = mom;
	dimensions = dim;
	visible = vis;
	canInteractWith = canInt;
	this->tex = tex;
	curIndexFrame = begInd;
	startingIndexFrame = begInd;
	endingIndexFrame = endInd;
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
	
	float alpha, beta, mu, nu; //alpha è la forza per ogni tick in cui è premuto il tasto, 
	//beta è la costante di resistenza(tipo attrito)
	//mu è la velocità massima
	//nu è la forza dopo un tick di forza partendo da fermo (resistenza statica) non utilizzato
	alpha = 1;
	mu = 20;
	beta = 0.50 * 9.81 * mass;
	nu = glm::min<float>(1.2*beta * mass, alpha); //ragionevole

	glm::vec2 oldMomentum = momentum;
	glm::vec2 oldVelocity = oldMomentum / mass;
	glm::vec2 forceInput;
	glm::vec2 forceStaticResistance;

	if (false)
	{
		//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "W is pressed");
		forceInput.y = 1;

	}
	else if (false)
	{
		//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "S is pressed");
		forceInput.y = -1;
	}
	else
	{
		forceInput.y = 0;
	}
	if (false)
	{
		//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "D is pressed");
		forceInput.x = 1;
	}
	else if (false)
	{
		//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "A is pressed");
		forceInput.x = -1;
	}
	else
	{
		forceInput.x = 0;
	}

	glm::normalize(forceInput);

	if (oldVelocity.x > -0.1 && oldVelocity.x < 0.1)
		forceStaticResistance.x = -nu * forceInput.x;

	if (oldVelocity.y > -0.1 && oldVelocity.y < 0.1)
		forceStaticResistance.x = -nu * forceInput.y;

	glm::vec2 direction = oldMomentum;
	
	glm::normalize(direction);

	glm::vec2 force = alpha * forceInput - beta * direction + forceStaticResistance; //la forza totale è quella di input meno la viscosità

	momentum = oldMomentum + force;

	glm::vec2 vel = momentum / mass;
	
	position += vel * dt; //calcolo spostamento dalla velocità

}


GameObject::~GameObject()
{
}
