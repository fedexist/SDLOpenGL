#pragma once

class EventHandler
{
	friend class Core;
public:
	EventHandler();
	EventHandler(Core*);
	~EventHandler();
	void processEvents(GameClass*);
	static void setQuitEvent(bool);
	static bool getQuitEvent();

private:
	static bool quitEvent;
	const Uint8* currentKeyStates;
	SDL_Event event;
	Core* core;

};

