#include "stdafx.h"
#include "Layout.h"


Layout::Layout(glm::vec2 bgDim, int xNum, int yNum)
{
	backgroundDim = bgDim;
	gridDim = glm::vec2(xNum, yNum);
	bgUnitDim = glm::vec2(1/gridDim.x, 1/gridDim.y);
}

glm::vec2 Layout::centerCoor(glm::vec2 objDim)
{
	float coorX = (backgroundDim.x / objDim.x) / 2 - 0.5f;
	float coorY = (backgroundDim.y / objDim.y) / 2 - 0.5f;

	return glm::vec2(coorX, coorY);
}

glm::vec2 Layout::positionObject(glm::vec2 objDim, int xCell, int yCell)
{
	float coorX = (xCell * bgUnitDim.x) * (backgroundDim.x / objDim.x) - 0.5f;
	float coorY = (yCell * bgUnitDim.y) * (backgroundDim.y / objDim.y) - 0.5f;

	return glm::vec2(coorX, coorY);
}


Layout::~Layout()
{
}
