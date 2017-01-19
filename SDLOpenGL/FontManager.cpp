#include "stdafx.h"
#include "FontManager.h"


//	TODO: Migliorare il font manager

bool FontManager::init()
{
	if (TTF_Init() == -1)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_TTF could not initialize! SDL Error: %s\n", TTF_GetError());
		return false;
	}

	return true;
}

bool FontManager::loadFont(std::string tag, std::string path, int pointSize)
{
	TTF_Font* font = TTF_OpenFont((fonts_path + path).c_str(), pointSize);
	if(font == nullptr)
	{
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Error loading font! %s", TTF_GetError());
		return false;
	}

	fontMap.put(tag, font);
	pointSizeMap.put(tag, pointSize);

	return true;

}

TTF_Font* FontManager::retrieveFont(std::string tag)
{
	TTF_Font* font = fontMap.get(tag);

	if (font == nullptr)
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Error retrieving font!");

	return font;


}

int FontManager::retrieveSize(std::string tag)
{
	int size = pointSizeMap.get(tag);

	if (size == 0)
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Error retrieving pointSize!");

	return size;

}

FontManager::FontManager()
{
}


FontManager::~FontManager()
{
}
