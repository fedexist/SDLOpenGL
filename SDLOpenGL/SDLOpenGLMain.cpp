#include "stdafx.h"
#include "GameClass.h"

GameClass game = GameClass("Morte's Quest");

int main(int argc, char* argv[])
{

	Core core = Core(1280, 720, &game);

	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

	if (!core.init())
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Core Initialization failed\n");
		return -1;
	}
	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Core Initialization ok\n");
	while (!core.checkQuitEvent())
	{

		core.handleEvents();
		core.update();
		core.render();

	}
	core.quit();
	return 0;
}

