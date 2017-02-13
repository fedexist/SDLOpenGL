#pragma once
#include "GameObject.h"
#include "DrawingPlane.h"
#include "Player.h"
#include "Camera2D.h"
#include "AudioManager.h"
#include "FontManager.h"
#include "ButtonMenu.h"
#include "Portal.h"
#include "Chest.h"

typedef enum GameState
{
	LAUNCHER,
	GAME,
	HELP,
	GAMEOVER,
	VICTORY,
	EXIT
}GameState;

class GameClass
{
	friend class Core;

	std::string windowTitle;

	std::vector<GameObject*> gameObjectArray;
	std::vector<GameObject*> allObjectsFactory;
	std::vector<AI*> allAisArray;
	std::vector<Chest*> allChestsArray;
	std::vector<Player*> allEnemiesArray;
	std::vector<Portal*> portalArray;

	Player* player_ = nullptr;
	Player* centerDummy = nullptr;

	std::vector<GLuint*> currentLevelLayout;
	std::vector<GLint*> currentLevelLayout_o;
	std::vector<GLint*> currentLevelLayout_l;

	std::vector< std::vector<GLuint*> > cachedLevelLayouts;
	std::vector< std::vector<GLint*> > cachedLevelLayouts_o;
	std::vector< std::vector<GLint*> > cachedLevelLayouts_l;


	std::vector<LTexture2D> allTextures;
	unsigned int levelLayoutW, levelLayoutH;
	std::string levelPath = "./assets/levels/";

	DrawingPlane plane;
	LWindow* window;	
	ButtonMenu* menu;
	Camera2D* camera;
	GameState gameState;
	AudioManager* audio_manager;
	FontManager* font_manager;

	int AIHandicapAI = 2; //quando il contatore arriva 2 aggiorno le AI
	int	AIHandicapCounter=0;

	int timerToWin = 0;

	void quit();

public:
	GameClass();
	GameClass(std::string title);
	~GameClass();
	void update(float);
	void loadMedia();
	void render();
	void loadLevelLayout(std::string, unsigned int, unsigned int);

	void populateWorld();
	void emptyWorld();
	void portalSetup(Portal* portalUpLeft, Portal* portalUpRight, Portal* portalDownLeft, Portal* portalDownRight);

	void handleMouseEvents(const SDL_Event& e);
	void handleEvents(SDL_Event& e);
	void handleKeyboardEvents();
	
	void setObjectWorldKnowledge(GameObject*); //The World gives knowledge to the gameobject about its whereabouts

	void setCamera2D(Camera2D* camera);
	void setGameState(GameState gs);
	void setAudioManager(AudioManager* audio_manager);

	float distance(GameObject* obj1, GameObject* obj2) const;
	void setFontManager(FontManager* font_manager);
};

