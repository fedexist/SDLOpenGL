#include "stdafx.h"
#include <functional>
#include "EventHandler.h"
#include "DrawingPlane.h"

Core::Core()
{
	dt = 0.0f;
}

/* It's actually not needed
Core::Core(int w, int h, std::function<::Internalupdate()> update)
{
	window_ = LWindow(this, w, h);
	event_handler_ = EventHandler();
	dt = 0.0f;
	startTime = 0.0f;
	Internalupdate = update();
}


Core::Core(int w, int h, ::Internalupdate update, ::InternalRender render)
{
	window_ = LWindow(this, w, h);
	event_handler_ = EventHandler();
	dt = 0.0f;
	startTime = 0.0f;
	Internalupdate = update;
	InternalRender = render;
}*/
Core::Core(int w, int h, GameClass* game)
{
	window_ = LWindow(this, w, h);
	event_handler_ = EventHandler();
	dt = 0.0f;
	startTime = 0.0f;
	Game = game;
}


void Core::quit()
{
	window_.free();
	SDL_DestroyRenderer(mRenderer);

	SDL_Quit();

}

Core::~Core()
{
	window_.free();
	SDL_DestroyRenderer(mRenderer);

}

bool Core::init()
{
	//Initialization flag
	bool success = true;


	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{

		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );


		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		if( !window_.init() )
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gl_handler_.gl_context_ = SDL_GL_CreateContext( window_.mWindow );

			if( gl_handler_.gl_context_ == nullptr )
			{
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Initialising glew\n");
				//Initialize GLEW
				glewExperimental = GL_TRUE; 
				GLenum glewError = glewInit();
				if( glewError != GLEW_OK )
				{
					SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
				}

				//Initialize OpenGL
				if( !gl_handler_.initGL(&window_) )
				{
					SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize OpenGL!\n" );
					success = false;
				}

				//Use Vsync
				if( SDL_GL_SetSwapInterval( 1 ) < 0 )
				{
					SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
				}

				gl_handler_.testFunction();

				//Create renderer for window
				/*window_.mRenderer = window_.createRenderer();
				if( window_.mRenderer == nullptr )
				{
					SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
					success = false;
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor( window_.mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if( !( IMG_Init( imgFlags ) & imgFlags ) )
					{
						SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
						success = false;
				}*/
			}
		}
	}

	return success;
}

void Core::renderPresent()
{
	SDL_RenderPresent( mRenderer );
}

void Core::handleEvents()
{
	startTime = SDL_GetTicks();

	event_handler_.processEvents();

}

void Core::update() const
{
	/*if (Internalupdate == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "There is no valid update(dt) function assigned");
		return;
	}
		
	Internalupdate(dt);*/
	Game->update(dt);
}

void Core::render()
{
	gl_handler_.gl_renderer_.Render(Game);
	dt = SDL_GetTicks() - startTime;
	SDL_GL_SwapWindow( window_.getSDLWindow());
	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Delta time is: %f", dt);

}

LWindow* Core::getWindow()
{
	return &window_;
}

bool Core::checkQuitEvent()
{
	return EventHandler::getQuitEvent();
}





