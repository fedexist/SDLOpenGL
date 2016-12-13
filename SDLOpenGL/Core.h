#pragma once
#include "stdafx.h"
#include "LWindow.h"
#include "GLHandler.h"
#include "EventHandler.h"
#include "GameClass.h"
#include "AudioManager.h"

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
		void update();
		void render();
		LWindow* getWindow();
		void updateProjection(GLfloat resize_w, GLfloat resize_h) const;
		static bool checkQuitEvent();
		//void FreeCameraMovement();
		~Core();
		Internalupdate Internalupdate;
		InternalRender InternalRender;
		
private:
		LWindow window_;
		SDL_Renderer* mRenderer;
		GLHandler gl_handler_;
		EventHandler event_handler_;
		GameClass* Game;
		Camera2D* camera;
		AudioManager audio_manager_;
		
		//const double dt = 10.0f;
		double startTime, frameTime, updateTime, lastTimeStamp;
};

