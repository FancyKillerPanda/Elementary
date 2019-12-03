#pragma once

#include <string>

#include <SDL/SDL_mixer.h>

namespace el
{

class Sound
{
public:
	// The sound that is being played
	Mix_Chunk* chunk = nullptr;

private:
	bool isPlaying = false;

	int channel = -1;
	std::string filePath;

public:
	Sound(std::string filePath, unsigned char volume = 64);

	void play(unsigned int numberOfLoops = 0);
	void stop();
	void fadeOut(unsigned int duration); // NOTE(fkp): Duration is in milliseconds

	static void setMasterVolume(unsigned char volume);
	void setVolume(unsigned char volume);

	unsigned char getVolume();
	bool getIsPlaying() { return isPlaying; }
	int getChannel() { return channel; }
};
	
}
