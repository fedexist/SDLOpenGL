#pragma once
class Layout
{

	glm::vec2 backgroundDim;
	glm::vec2 gridDim;
	glm::vec2 bgUnitDim;

public:
	Layout(glm::vec2 backgroundDim, int xNum, int yNum);
	~Layout();

	//restituisce le coordinate (in "unità oggetto") per avere l'oggetto 
	//centrato nel punto (xCell,yCell) in una griglia di dimensioni "gridDim"
	glm::vec2 positionObject(glm::vec2 objDim, int xCell, int yCell);

	//restituisce le coordinate (in "unità oggetto") per avere l'oggetto al centro
	glm::vec2 centerCoor(glm::vec2 objDim); 

};

