#pragma once
#include "stdafx.h"


class LWindow
{
	friend class Core;
	public:
		LWindow();
		LWindow(Core* core, int w, int h);

		 //Creates window bool 
		bool init(std::string title); 
		//Creates renderer from internal window 
		SDL_Renderer* createRenderer() const; 
		//Handles window events 
		void handleEvent( SDL_Event& e ); 
		//Deallocates internals 
		void free(); 
		//Window dimensions 
		int getWidth() const; 
		int getHeight() const;
		void setWidth(int w);
		void setHeight(int h);
		void setDimensions(int w, int h);
		//Window focii 
		bool hasMouseFocus() const; 
		bool hasKeyboardFocus() const; 
		bool isMinimized() const;

		SDL_Window* getSDLWindow();
	
		virtual ~LWindow();

		 private: 
		Core* coreInstance;
		//Window data 
		SDL_Window* mWindow;
		//Window dimensions 
		int mWidth; int mHeight; 
		//Window focus 
		bool mMouseFocus; 
		bool mKeyboardFocus; 
		bool mFullScreen; 
		bool mMinimized;
};

