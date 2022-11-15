#ifndef MUSIC
#define MUSIC
#include "SDL_mixer.h"
#include <iostream>
#include <string>

class Music{
	private:
		Mix_Music* music;
	public:
		Music();
		Music(std::string file);
		~Music();
		void Play(int times = -1);
		void Stop(int msToStop = 1500);
		void Open(std::string file);
		bool IsOpen() { return !!music; }
};

#endif // MUSIC

