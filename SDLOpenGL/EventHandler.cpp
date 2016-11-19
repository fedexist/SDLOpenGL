#include "stdafx.h"
#include "EventHandler.h"

bool EventHandler::quitEvent;

static int QuitEventFilter(void* userdata, SDL_Event* event)
{
	
	if (event->type == SDL_QUIT)
		EventHandler::setQuitEvent(true);

	return 0;
}

EventHandler::EventHandler()
{
	currentKeyStates = SDL_GetKeyboardState( nullptr );
	SDL_AddEventWatch( QuitEventFilter , nullptr);
	quitEvent = false;
	core = nullptr;
}

EventHandler::EventHandler(Core* c)
{
	currentKeyStates = SDL_GetKeyboardState( nullptr );
	SDL_AddEventWatch( QuitEventFilter , nullptr);
	quitEvent = false;
	core = c;

}


EventHandler::~EventHandler()
{
	SDL_DelEventWatch(QuitEventFilter, nullptr);
}


void EventHandler::processEvents()
{
	if (SDL_PollEvent(&event) != 0)
	{
		//window event handling
		core->getWindow()->handleEvent(event);
	}
		
}

void EventHandler::setQuitEvent(bool b)
{
	quitEvent = b;
}

bool EventHandler::getQuitEvent()
{
	return quitEvent;
}
