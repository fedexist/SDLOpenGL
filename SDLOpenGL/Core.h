#pragma once
#include "stdafx.h"
#include "LWindow.h"
#include "GLHandler.h"
#include "EventHandler.h"
#include <functional>

typedef void(*Internalupdate)(float dt);

class Core
{
	public:
		Core();
		Core(int w, int h, std::function<::Internalupdate()> update);
		Core(int w, int h, Internalupdate);
		void quit();
		bool init();
		void renderPresent();
		void handleEvents();
		void update() const;
		void render();
		LWindow* getWindow();
		static bool checkQuitEvent();
		~Core();
		Internalupdate Internalupdate;
	private:
		LWindow window_;
		SDL_Renderer* mRenderer;
		GLHandler gl_handler_;
		EventHandler event_handler_;
		float dt, startTime;
};

