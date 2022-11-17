#include "Music.h"

Music::Music() {
	music = nullptr;
}

Music::Music(std::string file):Music() {
	Mix_VolumeMusic(10);
	Open(file);
}

Music::~Music() {
	Stop();
	Mix_FreeMusic(music);
}

void Music::Play(int times) {
	if (music != nullptr) {
		Mix_PlayMusic(music, times);
	}
}

void Music::Stop(int msToStop) {
	if (music) {
		Mix_FadeOutMusic(msToStop);
	}
}

void Music::Open(std::string file) {
	music = Mix_LoadMUS(file.c_str());
	if (music == nullptr) {
		std::cout << "Mix_LoadMUS failed: " << SDL_GetError() << "\n";
		Music::~Music();
	}
}