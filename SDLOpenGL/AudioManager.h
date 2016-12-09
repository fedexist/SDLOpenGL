#pragma once
#include <map>
#include "HashTable.h"

typedef enum { PLAY, STOP, PAUSE, RESUME } musicActions;

class AudioManager
{
	Hashtable< std::string, Mix_Chunk* > effectsMap;
	Hashtable< std::string, Mix_Music* > musicMap;

	unsigned int allocatedChannels = 32; // Default number of channels available

public:
	AudioManager();
	~AudioManager();
	bool init();
	bool LoadSoundEffect(std::string path, std::string key);
	bool LoadMusic(std::string path, std::string key);
	void ManageMusic(musicActions action, std::string key);
	void playSoundEffect(std::string key);
	static void setEffectsVolume(float volumePercent); //sets volume for all the allocated channels
	void setEffectsVolume(std::string key, float volumePercent); //sets volume for specific sound effect
	static void setMusicVolume(float volumePercent); //sets volume for music only
	void quit();
};

