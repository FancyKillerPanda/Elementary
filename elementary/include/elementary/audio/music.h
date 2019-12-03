#pragma once

#include <string>

#include <SDL/SDL_mixer.h>

namespace el
{

class Music
{
public:
	// The music that is being played
	Mix_Music* music = nullptr;

private:
	bool isPlaying = false;

	std::string filePath;

public:
	Music(std::string filePath, unsigned char volume = 64);

	void play(unsigned int numberOfLoops = 0);
	void pause();
	void resume();
	void togglePaused();

	void setVolume(unsigned char volume);
	
	unsigned char getVolume();
	bool getIsPlaying() { return isPlaying; }
};
	
}
