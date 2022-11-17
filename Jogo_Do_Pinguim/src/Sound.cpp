#include "Sound.h"

Sound::Sound(GameObject& associated) : Component(associated) {
	chunk = nullptr;
}

Sound::Sound(GameObject& associated, std::string file) : Sound(associated) {
	Open(file);
}

std::vector<Mix_Chunk*> vectorCh{32};

void channelCallback(int channel) {
	Mix_FreeChunk(vectorCh[channel]);
}

Sound::~Sound() {
	if (chunk != nullptr) {
		vectorCh[channel] = chunk;
		Mix_ChannelFinished(channelCallback);
	}
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
	chunk = Mix_LoadWAV(file.c_str());
	if (chunk == nullptr) {
		std::cout << "Mix_LoadWAV failed: " << SDL_GetError() << "\n";
		Sound::~Sound();
	}
	Mix_VolumeChunk(chunk, 20);
}

void Sound::Update(float dt) {

}

void Sound::Render() {

}

bool Sound::Is(std::string type) {
	return (type == "Sound");
}