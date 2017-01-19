#pragma once
class DeathMenu
{
	friend class GameClass;
	std::vector<Button*> buttons;
	Text* deathText;
	Background* background;
	LWindow* window;
	glm::vec2 dimButton;
	glm::vec2 dimBackground;
	LTexture2D* deadPlayer;
public:
	DeathMenu(LWindow*, FontManager*);
	~DeathMenu();
	void render();
	int selectedButton;
	void selectedCheck();
	float centredCoor(float dimPlane, float dimObj);
	void onUpdateWindow();
	glm::vec2 relativeCoor2pxCoor(glm::vec2 relCoor, glm::vec2 dimensions);
};

