#include "Sound.h"
#include "Resources.h"

Sound::Sound(GameObject& associated) : Component(associated) {
	chunk = nullptr;
}

Sound::Sound(GameObject& associated, std::string file) : Sound(associated) {
	Open(file);
}

Sound::~Sound() {
}

void Sound::Play(int times) {
	if (chunk != nullptr) {
		channel = Mix_PlayChannel(-1,chunk,times-1);
		if (channel == -1) {
			std::cout << "Mix_PlayChannel failed: " << SDL_GetError() << "\n";
		}
	}
}

void Sound::Stop() {
	if (chunk != nullptr) {
		Mix_HaltChannel(channel);
	}
}

void Sound::Open(std::string file) {
	chunk = Resources::GetSound(file);
}

void Sound::Update(float dt) {

}

void Sound::Render() {

}

bool Sound::Is(std::string type) {
	return (type == "Sound");
}