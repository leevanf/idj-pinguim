#include "Resources.h"
#include "Game.h"
#include <utility>
std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;
SDL_Texture* Resources::GetImage(std::string file) {
	if (imageTable.find(file) != imageTable.end()) {
		return imageTable[file];
	}
	else {
		SDL_Texture* image;
		image = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
		if (image == nullptr) {
			std::cout << "IMG_LoadTexture failed: " << SDL_GetError() << "\n";
			return image;
		}
		imageTable.insert(std::make_pair(file, image));
		return image;
	}
}

void Resources::ClearImages() {
	for (auto it = imageTable.begin(); it != imageTable.end(); ++it) {
		SDL_DestroyTexture(it->second);
	}
	imageTable.clear();
}

Mix_Music* Resources::GetMusic(std::string file) {
	if (musicTable.find(file) != musicTable.end()) {
		return musicTable[file];
	}
	else {
		Mix_Music* music;
		music = Mix_LoadMUS(file.c_str());
		if (music == nullptr) {
			std::cout << "Mix_LoadMUS failed: " << SDL_GetError() << "\n";
			return music;
		}
		musicTable.insert(std::make_pair(file, music));
		return music;
	}
}

void Resources::ClearMusics() {
	for (auto it = musicTable.begin(); it != musicTable.end(); ++it) {
		Mix_FreeMusic(it->second);
	}
	musicTable.clear();
}

Mix_Chunk* Resources::GetSound(std::string file) {
	if (soundTable.find(file) != soundTable.end()) {
		return soundTable[file];
	}
	else {
		Mix_Chunk* sound;
		sound = Mix_LoadWAV(file.c_str());
		if (sound == nullptr) {
			std::cout << "Mix_LoadWAV failed: " << SDL_GetError() << "\n";
			return sound;
		}
		Mix_VolumeChunk(sound, 20);
		soundTable.insert(std::make_pair(file, sound));
		return sound;
	}
}

void Resources::ClearSounds() {
	for (auto it = soundTable.begin(); it != soundTable.end(); ++it) {
		Mix_FreeChunk(it->second);
	}
	soundTable.clear();
}