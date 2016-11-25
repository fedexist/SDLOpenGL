#pragma once
#include "stdafx.h"
#include "LWindow.h"
#include "GLHandler.h"
#include "EventHandler.h"
#include "GameClass.h"
#include "Camera.h"

typedef void(*Internalupdate)(float dt);
typedef void(*InternalRender)();

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
		void update() const;
		void render();
		LWindow* getWindow();
		void updateProjection();
		static bool checkQuitEvent();
		void FreeCameraMovement();
		~Core();
		Internalupdate Internalupdate;
		InternalRender InternalRender;
		
private:
		LWindow window_;
		SDL_Renderer* mRenderer;
		GLHandler gl_handler_;
		EventHandler event_handler_;
		double dt, startTime;
		GameClass* Game;
		//Camera camera;
};

