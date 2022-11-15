#include "Sprite.h"
#include "Game.h"

Sprite::Sprite() {
	texture = nullptr;
	width = 0;
	height = 0;
}

Sprite::Sprite(std::string file):Sprite() {
	Open(file);
}

Sprite::~Sprite() {
	if (texture) {
		SDL_DestroyTexture(texture);
	}
}

void Sprite::Open(std::string file) {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
	texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
	if (texture == nullptr) {
		std::cout << "IMG_LoadTexture failed: " << SDL_GetError() << "\n";
		return;
	}
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render(int x, int y) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = clipRect.w;
	dst.h = clipRect.h;
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dst);
}