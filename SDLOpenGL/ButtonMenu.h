#pragma once

typedef enum MenuState
{
	LAUNCHERM,
	HELPM,
	GAMEOVERM,
	VICTORYM

} MenuState;

class ButtonMenu
{
	friend class GameClass;


	class ImageObject
	{
		glm::vec2 position;
		glm::vec2 dimension;
		LTexture2D* pic;

	public:
		ImageObject(glm::vec2 pos, glm::vec2 dim, LTexture2D* tex) { position = pos; dimension = dim; pic = tex; };
		~ImageObject();

		void render() { pic->drawSprite(position.x, position.y, 0, 0); };
	};


	Layout* layout;
	glm::vec2 dimBackground;
	glm::vec2 dimButton;
	LWindow* window;
	MenuState menuState;
	int selectedButton;

	//launcher elements
	std::vector<Button*> launcherButtons;
	ImageObject* title;
	Background* launcherBackground;

	//help elements
	std::vector<Button*> helpButtons;
	ImageObject* commandsBackground;
	std::vector<Text*> commandsTexts;
	std::vector<ImageObject*> commandsPics;
	Background* helpBackground;

	//gameover elements
	std::vector<Button*> gameoverButtons;
	Text* gameoverText;
	//Background* gameoverBackground;

	//victory elements
	std::vector<Button*> victoryButtons;
	Text* victoryText;
	//Background* victoryBackground;

public:
	ButtonMenu(LWindow* window, FontManager* fontManager);
	~ButtonMenu();

	void render();
	void selectedCheck(std::vector<Button*> buttons);
	void onUpdateWindow();
	void setMenuState(MenuState menuState);
	glm::vec2 relativeCoor2pxCoor(glm::vec2 relCoor, glm::vec2 dimensions);
	void rel2pxButtonsCoor(std::vector<Button*>);
	float centredCoor(float, float);
};

