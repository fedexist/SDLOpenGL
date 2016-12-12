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

	/*	TODO: Da aggiungere:
	 *		- Fading In/out on play and stop [DONE]
	 *		- Sound Effect / Channel grouping
	 *		- Sound Effect management (single and grouped)
	 *
	 */

	AudioManager();
	~AudioManager();
	bool init();
	bool LoadSoundEffect(std::string path, std::string key);
	bool LoadMusic(std::string path, std::string key);
	void ManageMusic(musicActions action, std::string key, Mix_Fading fading = MIX_NO_FADING, int fadingValue = 0); //fading value in ms
	void playSoundEffect(std::string key);
	static void setEffectsVolume(float volumePercent); //sets volume for all the allocated channels
	void setEffectsVolume(std::string key, float volumePercent); //sets volume for specific sound effect
	static void setMusicVolume(float volumePercent); //sets volume for music only
	void quit();
};

