#include "stdafx.h"
#include "LWindow.h"

LWindow::LWindow()
{
	mWindow = nullptr; 
	mMouseFocus = false; 
	mKeyboardFocus = false; 
	mFullScreen = false; 
	mMinimized = false; 
	mWidth = 0;
	mHeight = 0;
}

LWindow::LWindow(Core* core, int width, int height)
{
	mWindow = nullptr; 
	mMouseFocus = false; 
	mKeyboardFocus = false; 
	mFullScreen = false; 
	mMinimized = false; 
	mWidth = width;
	mHeight = height;
	coreInstance = core;
}

bool LWindow::init()
{
	//Create window
	mWindow = SDL_CreateWindow( "Window Title", 
								SDL_WINDOWPOS_UNDEFINED, 
								SDL_WINDOWPOS_UNDEFINED, 
								mWidth, 
								mHeight, 
								SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	if( mWindow != nullptr )
	{
		mMouseFocus = true;
		mKeyboardFocus = true;
	}

	return mWindow != nullptr;
}

SDL_Renderer* LWindow::createRenderer() const
{
	return SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
}

void LWindow::handleEvent( SDL_Event& e )
{
	//Window event occured
	if( e.type == SDL_WINDOWEVENT )
	{
		//Caption update flag
		bool updateCaption = false;

		switch( e.window.event )
		{
			//Get new dimensions and repaint on window size change
			case SDL_WINDOWEVENT_SIZE_CHANGED:
			mWidth = e.window.data1;
			mHeight = e.window.data2;
			SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Window resized");
			SDL_GL_SwapWindow(mWindow);
			coreInstance->renderPresent();
			break;

			//Repaint on exposure
			case SDL_WINDOWEVENT_EXPOSED:
			SDL_GL_SwapWindow(mWindow);
			coreInstance->renderPresent();
			break;

			//Mouse entered window
			case SDL_WINDOWEVENT_ENTER:
			mMouseFocus = true;
			updateCaption = true;
			break;
			
			//Mouse left window
			case SDL_WINDOWEVENT_LEAVE:
			mMouseFocus = false;
			updateCaption = true;
			break;

			//Window has keyboard focus
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			mKeyboardFocus = true;
			updateCaption = true;
			break;

			//Window lost keyboard focus
			case SDL_WINDOWEVENT_FOCUS_LOST:
			mKeyboardFocus = false;
			updateCaption = true;
			break;

			//Window minimized
			case SDL_WINDOWEVENT_MINIMIZED:
			mMinimized = true;
			break;

			//Window maxized
			case SDL_WINDOWEVENT_MAXIMIZED:
			mMinimized = false;
			break;
			
			//Window restored
			case SDL_WINDOWEVENT_RESTORED:
			mMinimized = false;
			break;
		default: break;
		}
	}
	//Enter exit full screen on return key
	else if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN )
	{
		if( mFullScreen )
		{
			SDL_SetWindowFullscreen( mWindow, SDL_FALSE );
			mFullScreen = false;
		}
		else
		{
			SDL_SetWindowFullscreen( mWindow, SDL_TRUE );
			mFullScreen = true;
			mMinimized = false;
		}
	}
}

void LWindow::free()
{
	if( mWindow != nullptr )
	{
		SDL_DestroyWindow( mWindow );
	}
	mMouseFocus = false;
	mKeyboardFocus = false;
	mWidth = 0;
	mHeight = 0;
}

int LWindow::getWidth() const
{
	return mWidth;
}

int LWindow::getHeight() const
{
	return mHeight;
}

void LWindow::setWidth(int w)
{
	mWidth = w;
}

void LWindow::setHeight(int h)
{
	mHeight = h;
}

void LWindow::setDimensions(int w, int h)
{
	mWidth = w;
	mHeight = h;
}

bool LWindow::hasMouseFocus() const
{
	return mMouseFocus;
}

bool LWindow::hasKeyboardFocus() const
{
	return mKeyboardFocus;
}

bool LWindow::isMinimized() const
{
	return mMinimized;
}

SDL_Window* LWindow::getSDLWindow()
{
	return mWindow;
}


LWindow::~LWindow()
{
	free();
}
