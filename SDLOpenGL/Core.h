#pragma once
#include "LWindow.h"
#include "GLHandler.h"
#include "EventHandler.h"
#include "GameClass.h"
#include "AudioManager.h"
#include "FontManager.h"
#include "ButtonMenu.h"

typedef void(*Internalupdate)(float dt);
typedef void(*InternalRender)();

template<typename T>
struct deleter : std::unary_function<const T*, void>
{
	void operator() (const T *ptr) const
	{
		delete ptr;
	}
};

struct renderer : std::unary_function<const Portal*, void>
{
	void operator() (Portal *ptr) const
	{
		ptr->render();
	}
};

struct noPortalRenderer : std::unary_function<const GameObject*, void>
{
	void operator() (GameObject *ptr) const
	{
		if(!dynamic_cast<Portal*>(ptr))
			ptr->render();
	}
};

class Core
{
	public:
		Core();
		//Core(int w, int h, std::function<::Internalupdate()> update);
		//Core(int w, int h, Internalupdate, InternalRender);
		Core(int w, int h, GameClass*);
		void quit();
		bool init();
		void renderPresent();
		void handleEvents();
		void update();
		void render();
		LWindow* getWindow();
		void updateProjection(GLfloat resize_w, GLfloat resize_h) const;
		static bool checkQuitEvent();
		//void FreeCameraMovement();
		~Core();
		Internalupdate Internalupdate;
		InternalRender InternalRender;
		ButtonMenu* getMenu();

private:
		LWindow window_;
		SDL_Renderer* mRenderer;
		GLHandler gl_handler_;
		EventHandler event_handler_;
		GameClass* Game;
		Camera2D* camera;
		AudioManager audio_manager_;
		FontManager font_manager_;
		ButtonMenu* menu;
		
		//const double dt = 10.0f;
		double startTime, frameTime, updateTime, lastTimeStamp;
};

