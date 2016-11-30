#pragma once
#include "GameObject.h"
#include "DrawingPlane.h"
#include "Player.h"
#include "Camera2D.h"



class GameClass
{
	std::vector<GameObject*> gameObjectArray;
	std::vector<GameObject*> allObjectsFactory;
	Player* player_ = nullptr;
	DrawingPlane plane;
	std::vector<GLuint*> currentLevelLayout;

	std::vector<GLuint*> currentLevelLayout_o;

	std::vector<GLuint*> currentLevelLayout_l;

	std::vector<LTexture2D> allTextures;
	unsigned int leveLayoutW, levelLayoutH;
	std::string levelPath = "./assets/levels/";
	std::vector< std::vector<GLuint*> > cachedLevelLayouts;

	std::vector< std::vector<GLuint*> > cachedLevelLayouts_o;

	std::vector< std::vector<GLuint*> > cachedLevelLayouts_l;
	Camera2D* camera;

public:
	GameClass();
	~GameClass();
	void update(float);
	void loadMedia();
	void render();
	void loadLevelLayout(std::string, unsigned int, unsigned int);
	void handleMouseEvents(const SDL_Event& sdl_event);
	void handleEvents(SDL_Event& e);
	void handleKeyboardEvents();
	glm::vec2 positionToScreen(GameObject * obj);
	std::vector<GLuint*> getLevelLayout() const { return currentLevelLayout; } //probabilmente non necessaria
	void setCamera2D(Camera2D* camera);
};

