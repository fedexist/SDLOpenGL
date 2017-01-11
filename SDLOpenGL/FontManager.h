#pragma once
#include "HashTable.h"

class FontManager
{

	Hashtable<std::string, TTF_Font*> fontMap;
	Hashtable<std::string, int> pointSizeMap;
	const std::string fonts_path = "./assets/fonts/";
public:
	bool init();
	bool LoadFont(std::string tag, std::string path, int pointSize);
	TTF_Font* retrieveFont(std::string tag);
	int retrieveSize(std::string tag);
	FontManager();
	~FontManager();
};

