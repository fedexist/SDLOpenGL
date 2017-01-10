#pragma once
class Background
{
public:
	Background(std::string path, int w, int h);
	~Background();
	void render();
	glm::vec2 getBackgroundDim();

private:
	LTexture2D* backgroundTexture;
	glm::vec2 backgroundDim;
};

