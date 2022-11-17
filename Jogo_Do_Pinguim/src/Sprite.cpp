#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(GameObject& associated) : Component(associated) {
	texture = nullptr;
	width = 0;
	height = 0;
}

Sprite::Sprite(GameObject& associated, std::string file) : Sprite(associated) {
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
	mAssociated.box.w = (float)width;
	mAssociated.box.h = (float)height;
	SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render() {
	SDL_Rect dst;
	dst.x = (int)mAssociated.box.x;
	dst.y = (int)mAssociated.box.y;
	dst.w = clipRect.w;
	dst.h = clipRect.h;
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dst);
}

void Sprite::Update(float dt) {

}

bool Sprite::Is(std::string type) {
	return (type == "Sprite");
}