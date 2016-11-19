#pragma once
#include "stdafx.h"

class EventHandler
{
	friend class Core;
public:
	EventHandler();
	EventHandler(Core*);
	~EventHandler();
	void processEvents();
	static void setQuitEvent(bool);
	static bool getQuitEvent();

private:
	static bool quitEvent;
	const Uint8* currentKeyStates;
	SDL_Event event;
	Core* core;

};

