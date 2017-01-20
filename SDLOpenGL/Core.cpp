#include "stdafx.h"
#include <functional>
#include "EventHandler.h"

Core::Core()
{
	//dt = 0.0f;
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

//	REFACTOR: [RELEASE] Sistemare la struttura di cartelle del repository.

//	REFACTOR: [RELEASE] Core dovrebbe gestire i cicli di update e render con delle callback \
	InternalUpdate e InternalRender, la cui signature deve essere rispettata dalla GameClass, \
	che a questo punto, può avere qualsiasi nome

//	TODO: [RELEASE] Fornire layer di implementazione per IMGUI (https://github.com/ocornut/imgui) \
	

Core::Core(int w, int h, GameClass* game)
{
	window_ = LWindow(this, w, h);
	event_handler_ = EventHandler(this);
	audio_manager_ = AudioManager();
	//dt = 0.0f;
	startTime = 0.0f;
	Game = game;
	game->window = getWindow();
}


void Core::quit()
{
	window_.free();
	audio_manager_.quit();
	SDL_DestroyRenderer(mRenderer);

	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}

Core::~Core()
{
	window_.free();
	SDL_DestroyRenderer(mRenderer);

	audio_manager_.quit();
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();

}

bool Core::init()
{
	//Initialization flag
	bool success = true;

	
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
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
		if( !window_.init(Game->windowTitle) )
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

				camera = &gl_handler_.camera;
				camera->enablefreeMovement();

				//Use Vsync
				if( SDL_GL_SetSwapInterval(  1 ) < 0 )
				{
					SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
				}

				//gl_handler_.testFunction();

				//Create renderer for window
				mRenderer = window_.createRenderer();
				if( mRenderer == nullptr )
				{
					SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
					success = false;
				}
				else
				{
					//Initialize renderer color
					//SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0 );

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
						success = false;
					}
					/**/
					if( !audio_manager_.init() )
					{
						SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"SDL_Mixer could not initialize! SDL Error: %s\n", Mix_GetError() );
						success = false;
					} 
					if (!font_manager_.init())
					{
						SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_TTF could not initialize! SDL Error: %s\n", TTF_GetError());
						success = false;
					}
					else
					{
						font_manager_.loadFont("main_font", "general_font.ttf", 50);
						font_manager_.loadFont("death_font", "death_font.ttf", 100);
						Game->setFontManager(&font_manager_);
						Game->setAudioManager(&audio_manager_);
						Game->setCamera2D(camera);
						SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "About to loadMedia()\n");
						Game->loadMedia();
						

						//	TODO: [RELEASE] sistemare la parte seguente per rispettare l'agnosticismo di Core.

						launcher = new Launcher(getWindow(), &font_manager_);
						Game->launcher = launcher;
						help = new Help(getWindow(), &font_manager_);
						Game->help = help;
						deathMenu = new DeathMenu(getWindow(), &font_manager_);
						Game->deathMenu = deathMenu;
					}
						

				}

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
	
	event_handler_.processEvents(Game);
	startTime = SDL_GetTicks();
	frameTime = startTime - lastTimeStamp;
}

//	TODO: [RELEASE] eliminare launcher ed help per release finale \
	Core deve essere agnostico rispetto ai sistemi di mera logica di gioco. 

Launcher* Core::getLauncher()
{
	return launcher;
}

Help* Core::getHelp()
{
	return help;
}

DeathMenu* Core::getDeathMenu()
{
	return deathMenu;
}


void Core::update()
{
	/*if (Internalupdate == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "There is no valid update(dt) function assigned");
		return;
	}
		
	Internalupdate(dt);*/
	//CHANGEEEEE
	while(frameTime > updateTime )
	{
		double startUpdate = SDL_GetTicks();
		Game->update(1);
		updateTime = SDL_GetTicks() - startUpdate;
		if (updateTime < 1)
		{
			updateTime = 1.0f;
		}
		frameTime -= updateTime;

	}
		
}

void Core::render()
{

	lastTimeStamp = SDL_GetTicks() - frameTime;

	gl_handler_.gl_renderer_.Render(Game);


	SDL_GL_SwapWindow( window_.getSDLWindow());
	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Delta time is: %f", dt);

}

LWindow* Core::getWindow()
{
	return &window_;
}

void Core::updateProjection(GLfloat resize_w, GLfloat resize_h) const
{
	camera->resetProjection(window_.getWidth(), window_.getHeight(), resize_w, resize_h);
}

bool Core::checkQuitEvent()
{
	return EventHandler::getQuitEvent();
}