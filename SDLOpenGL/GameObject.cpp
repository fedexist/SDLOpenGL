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
	this->mass = mass; //Player mass (Mp) Player mass = 1 Mp
}

void GameObject::render()
{
	tex->drawSprite(position.x, position.y, 1, curIndexFrame);
}

void GameObject::update(float dt)
{

	handleAnims(dt);
	glm::vec2 forceInput = glm::vec2(0.f, 0.f);

	//movement
	handleMovement(dt, forceInput);

}

void GameObject::handleAnims(float dt)
{
	if ((--framePeriodIndex) == 0)
	{
		framePeriodIndex = tex->framePeriod;
		curIndexFrame -= startingIndexFrame;
		curIndexFrame = (curIndexFrame + 1) % (endingIndexFrame - startingIndexFrame);
		curIndexFrame += startingIndexFrame;
	}
}

void GameObject::handleMovement(float dt, glm::vec2 forceInput)
{
	float pxlToMeter = 1.8f / 64; //the distance in metres of a pixel, considered a man of 1.80 m and 64 pixels of the sprite 
								// m/pxl
	float mPToKg = 12.0f + 5.0f; //the weight of the player in kg, 12 kg is the weight of a skeleton of a man of 80kg, 5 kg for equipment
								//kg/mP
	float alpha, Fa, mu, Fas, v; //alpha � la forza per ogni tick in cui � premuto il tasto, 
	//Fa � la forza di attrito
	//mu � la costante di attrito
	//Fas � la forza di attrito statico
	v = 1; //velocit� sensata, 0 = fermo, 0.5 = camminata lenta 1 = camminata, 2 = corsa
	alpha = (100.06f + (2*v * 0.01f)) * (1/pxlToMeter) * (1/mPToKg); //Mp * pxl/s^2
	mu = 0.5;	//unitario real world number
	Fa = mu * (9.81 / pxlToMeter) * mass; //Mp * pxl/s^2
	Fas = glm::min<float>(1.2* Fa, alpha); //Mp * pxl/s^2

	glm::vec2 oldMomentum = momentum; //Mp * pxl/s
	glm::vec2 oldVelocity = oldMomentum / mass;// pxl/s
	glm::vec2 forceStaticResistance = glm::vec2(0, 0); //Mp * pxl/s^2


	if (dot(forceInput, forceInput) > 0)
		forceInput = normalize(forceInput); //versore


	if (oldVelocity.x > -0.1 && oldVelocity.x < 0.1)
		forceStaticResistance.x = -Fas * forceInput.x; //Mp * pxl/s^2 * versore = Mp * pxl/s^2 * versore

	if (oldVelocity.y > -0.1 && oldVelocity.y < 0.1)
		forceStaticResistance.y = -Fas * forceInput.y; //Mp * pxl/s^2 * versore = Mp * pxl/s^2 * versore


	glm::vec2 direction = oldMomentum;

	//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "direction %f %f",direction.x,direction.y);

	if (dot(direction, direction)> 0)
		direction = normalize(direction); //versore

	glm::vec2 force = alpha * forceInput - Fa * direction + forceStaticResistance; //la forza totale � quella di input meno la viscosit�

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


	position += vel * dt; //calcolo spostamento dalla velocit�
}

GameObject::~GameObject()
{
}
