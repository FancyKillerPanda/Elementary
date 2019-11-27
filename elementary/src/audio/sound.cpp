#include "audio/sound.h"

namespace el
{

Sound::Sound(std::string filePath, unsigned char volume)
	: filePath(filePath)
{
	chunk = Mix_LoadWAV(filePath.c_str());
	setVolume(volume);
}

void Sound::play(unsigned int numberOfLoops)
{
	// Plays on the first free channel
	channel = Mix_PlayChannel(-1, chunk, numberOfLoops);
	isPlaying = true;
}

void Sound::stop()
{
	Mix_HaltChannel(channel);
	channel = -1;

	isPlaying = false;
}

void Sound::fadeOut(unsigned int duration)
{
	Mix_FadeOutChannel(channel, (int) duration);
	channel = -1;

	isPlaying = false;
}

void Sound::setMasterVolume(unsigned char volume)
{
	Mix_Volume(-1, volume);
}

void Sound::setVolume(unsigned char volume)
{
	Mix_VolumeChunk(chunk, volume);
}

unsigned char Sound::getVolume()
{
	return (unsigned char) Mix_VolumeChunk(chunk, -1);
}
	
}
