#include "stdafx.h"
#include <functional>
#include "EventHandler.h"

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
	event_handler_ = EventHandler(this);
	dt = 0.0f;
	startTime = 0.0f;
	Game = game;
	//camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
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
					SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "About to loadMedia()\n");
					Game->loadMedia();
					Game->setCamera2D(camera);

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
						success = false;
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
	startTime = SDL_GetTicks();
	event_handler_.processEvents(Game);

}

void Core::update() const
{
	/*if (Internalupdate == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "There is no valid update(dt) function assigned");
		return;
	}
		
	Internalupdate(dt);*/
	//CHANGEEEEE
	Game->update(1);
}

void Core::render()
{

		//Free Camera Movement
	//FreeCameraMovement();
	gl_handler_.gl_renderer_.Render(Game);
	dt = SDL_GetTicks() - startTime;

	SDL_GL_SwapWindow( window_.getSDLWindow());
	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Delta time is: %f", dt);

}

LWindow* Core::getWindow()
{
	return &window_;
}

void Core::updateProjection(GLfloat resize_w, GLfloat resize_h) const
{
	camera->updateProjectionOnResize(window_.getWidth(), window_.getHeight(), resize_w, resize_h);
}

bool Core::checkQuitEvent()
{
	return EventHandler::getQuitEvent();
}

/*
void Core::FreeCameraMovement()
{


	const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);
	float local_dt = 1.0f;//(dt + 1) * 0.28f; //CHANGEEEEEE

	gl_handler_.cameraMass = 0.75f; //Parametro principale

	float alpha, beta, mu, nu; //alpha è la forza per ogni tick in cui è premuto il tasto, 
							//beta è la costante di resistenza(tipo attrito)
							//mu è la velocità massima
							//nu è la forza dopo un tick di forza partendo da fermo (resistenza statica) non utilizzato
	alpha = 1;
	mu = 20;
	beta = alpha/mu; //condizione per il quale a velocità massima mantenendo acceleratore la velocità sia costante
	nu = beta * gl_handler_.cameraMass; //ragionevole e inutilizzato

	float oldVelocityX = gl_handler_.cameraVelocityX;
	float oldVelocityY = gl_handler_.cameraVelocityY;
	float oldMomentumX = gl_handler_.cameraMomentumX;
	float oldMomentumY = gl_handler_.cameraMomentumY;
	float ForceInputX;
	float ForceInputY;
	if (currentKeyStates[SDL_SCANCODE_W])
	{
		//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "W is pressed");
		ForceInputY = 1;

	}
	else if (currentKeyStates[SDL_SCANCODE_S])
	{
		//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "S is pressed");
		ForceInputY = -1;
	}
	else
	{
		ForceInputY = 0;
	}
	if (currentKeyStates[SDL_SCANCODE_D])
	{
		//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "D is pressed");
		ForceInputX = 1;
	}
	else if (currentKeyStates[SDL_SCANCODE_A])
	{
		//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "A is pressed");
		ForceInputX = -1;
	}
	else
	{
		ForceInputX = 0;
	}

	if (ForceInputX != 0 && ForceInputY != 0) //se vado in diagonale normalizzo il vettore
	{
		ForceInputX *= sqrt(2) / 2;
		ForceInputY *= sqrt(2) / 2;
	}
	
	float StaticResistanceX = 0;
	float StaticResistanceY = 0;

	if (oldVelocityX > -0.1 && oldVelocityX < 0.1)
		StaticResistanceX = - nu * ForceInputX;
	
	if (oldVelocityY > -0.1 && oldVelocityY < 0.1)
		StaticResistanceY = -nu * ForceInputY;

	float ForceX = alpha * ForceInputX - beta * oldVelocityX + StaticResistanceX; //la forza totale è quella di input meno la viscosità
	float ForceY = alpha * ForceInputY - beta * oldVelocityY + StaticResistanceY;

	float MomX = oldMomentumX + ForceX * local_dt * 2; //integro la forza per aggiornare la quantità di moto
	float MomY = oldMomentumY + ForceY * local_dt * 2;

	gl_handler_.cameraMomentumX = MomX;
	gl_handler_.cameraMomentumY = MomY;

	float VelX = MomX / gl_handler_.cameraMass; //calcolo la velocità dalla quantità di moto
	float VelY = MomY / gl_handler_.cameraMass;

	gl_handler_.cameraVelocityX = VelX;
	gl_handler_.cameraVelocityY = VelY;

	//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "%f,%f,%f", VelX, VelY, sqrt(pow(VelX,2)+pow(VelY,2)));

	float translationX = VelX * local_dt * 2; //calcolo spostamento dalla velocità
	float translationY = VelY * local_dt * 2;

	gl_handler_.bottom += translationY;
	gl_handler_.top += translationY;
	gl_handler_.right += translationX;
	gl_handler_.left += translationX;

	

	glMatrixMode(GL_PROJECTION);
	
	glTranslatef(-translationX, -translationY, 0.0);
	SDL_PumpEvents();

}*/