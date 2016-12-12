#include "stdafx.h"
#include "AudioManager.h"

AudioManager::AudioManager()
{

}


AudioManager::~AudioManager()
{
}

bool AudioManager::init()
{

	int flags = MIX_INIT_MP3;
	if(Mix_Init(flags) & flags != flags) 
	{
		SDL_LogDebug(SDL_LOG_CATEGORY_AUDIO, "Mix_Init: Failed to init required ogg and mp3 support!\n");
		SDL_LogDebug(SDL_LOG_CATEGORY_AUDIO, "Mix_Init: %s\n", Mix_GetError());

		return false;
	}

	if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
	{
		return false;
	}
	Mix_AllocateChannels(allocatedChannels);

	return true;
}

bool AudioManager::LoadSoundEffect(std::string path, std::string key)
{
	Mix_Chunk* soundEffect = Mix_LoadWAV(path.c_str());

	if(soundEffect == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Sound effect cannot be loaded! Mix Error: %s\n", Mix_GetError() );
		return false;
	}

	effectsMap.put(key, soundEffect);

	return true;
}

bool AudioManager::LoadMusic(std::string path, std::string key)
{
	Mix_Music* mix_music = Mix_LoadMUS(path.c_str());

	if(mix_music == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Music cannot be loaded! Mix Error: %s\n", Mix_GetError() );
		return false;
	}

	musicMap.put(key, mix_music);

	return true;
}

void AudioManager::ManageMusic(musicActions action, std::string key, Mix_Fading fading, int fadingValue)
{
	Mix_Music* requestedMusic = musicMap.get(key);

	if(requestedMusic == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Cannot find requested track! Mix Error: %s\n", Mix_GetError() );
		return;
	}

	switch(action)
	{
		case PLAY:
				if (Mix_PausedMusic() || !Mix_PlayingMusic() && fading == MIX_FADING_IN)
				{
					SDL_LogDebug(0, "Let's play some faded music");
					Mix_FadeInMusic(requestedMusic, -1, fadingValue);
				} else if (Mix_PausedMusic() || !Mix_PlayingMusic() && fading != MIX_FADING_IN)
				{
					SDL_LogDebug(0, "Let's play some music");
					Mix_PlayMusic(requestedMusic, -1);
				}	
			break;
		case STOP: 
			if (Mix_PausedMusic() || !Mix_PlayingMusic() && fading != MIX_FADING_OUT)
				Mix_HaltMusic();
			else if (Mix_PausedMusic() || !Mix_PlayingMusic() && fading == MIX_FADING_OUT)
				Mix_FadeOutMusic(fadingValue);
			break;
		case PAUSE: 
			if (Mix_PlayingMusic())
				Mix_PauseMusic();			
			break;
		case RESUME:
			if (Mix_PausedMusic() || !Mix_PlayingMusic())
				Mix_ResumeMusic();
			break;
		default: break;
	}
}

void AudioManager::playSoundEffect(std::string key) 
{
	Mix_Chunk* requestedEffect = effectsMap.get(key);

	if(requestedEffect == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Cannot find requested track! Mix Error: %s\n", Mix_GetError() );
		return;
	}

	Mix_PlayChannel(-1, requestedEffect, 0);
}

void AudioManager::setEffectsVolume(float volumePercent)
{
	Mix_Volume( -1, volumePercent * MIX_MAX_VOLUME);
}

void AudioManager::setEffectsVolume(std::string key, float volumePercent)
{
	Mix_Chunk* requestedEffect = effectsMap.get(key);

	if(requestedEffect == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Cannot find requested track! Mix Error: %s\n", Mix_GetError() );
		return;
	}

	Mix_VolumeChunk( requestedEffect , volumePercent * MIX_MAX_VOLUME);
}

void AudioManager::setMusicVolume(float volumePercent)
{
	Mix_VolumeMusic( volumePercent * MIX_MAX_VOLUME);
}



void AudioManager::quit()
{
	for(auto m = musicMap.htmap.begin(); m != musicMap.htmap.end(); m++)
		Mix_FreeMusic(m->second);
	musicMap.htmap.clear();

	for(auto m = effectsMap.htmap.begin(); m != effectsMap.htmap.end(); m++)
		Mix_FreeChunk(m->second);
	effectsMap.htmap.clear();

	Mix_Quit();
	Mix_CloseAudio();
}
