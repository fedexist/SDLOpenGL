#pragma once
#include "GameObject.h"
#include "DrawingPlane.h"
#include "Player.h"
#include "Camera2D.h"
#include "Launcher.h"
#include <SDL_ttf.h>

typedef enum GameState
{
	LAUNCHER,
	GAME,
	CREDITS,

}GameState;

class GameClass
{
	friend class Core;
	std::vector<GameObject*> gameObjectArray;
	Player* player_ = nullptr;
	Launcher* launcher;
	DrawingPlane plane;
	std::vector<GLuint*> currentLevelLayout;
	std::vector<LTexture2D> allTextures;
	unsigned int leveLayoutW, levelLayoutH;
	std::string levelPath = "./assets/levels/";
	std::vector< std::vector<GLuint*> > cachedLevelLayouts;
	Camera2D* camera;
	GameState gameState;

	
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
	void setGameState(GameState gs);
};

