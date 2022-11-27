#include "Music.h"
#include "Resources.h"

Music::Music() {
	music = nullptr;
}

Music::Music(std::string file):Music() {
	Mix_VolumeMusic(10);
	Open(file);
}

Music::~Music() {
	Stop();
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
	music = Resources::GetMusic(file);
}