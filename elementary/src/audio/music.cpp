#include "audio/music.h"

namespace el
{

Music::Music(std::string filePath, unsigned char volume)
	: filePath(filePath)
{
	music = Mix_LoadMUS(filePath.c_str());
	setVolume(volume);
}

void Music::play(unsigned int numberOfLoops)
{
	Mix_PlayMusic(music, numberOfLoops);
	isPlaying = true;
}

void Music::pause()
{
	Mix_PauseMusic();
	isPlaying = false;
}

void Music::resume()
{
	Mix_ResumeMusic();
	isPlaying = true;
}

void Music::togglePaused()
{
	if (isPlaying)
	{
		pause();
	}
	else
	{
		resume();
	}
}

void Music::setVolume(unsigned char volume)
{
	Mix_VolumeMusic(volume);
}

unsigned char Music::getVolume() const
{
	return (unsigned char) Mix_VolumeMusic(-1);
}
	
}
