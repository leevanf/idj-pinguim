#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(GameObject& associated) : Component(associated) {
	texture = nullptr;
	width = 0;
	height = 0;
}

Sprite::Sprite(GameObject& associated, std::string file) : Sprite(associated) {
	Open(file);
}

Sprite::~Sprite() {

}

void Sprite::Open(std::string file) {
	texture = Resources::GetImage(file);
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
	Sprite::Render(mAssociated.box.x, mAssociated.box.y);
}

void Sprite::Render(float x, float y) {
	SDL_Rect dst;
	dst.x = (int)x + Camera::pos.x;
	dst.y = (int)y + Camera::pos.y;
	dst.w = clipRect.w;
	dst.h = clipRect.h;
	int renderCopyCode = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dst);
	if (renderCopyCode != 0) {
		std::cout << "SDL_RenderCopy failed: " << SDL_GetError() << "\n";
		exit(1);
	}
}

void Sprite::Update(float dt) {

}

bool Sprite::Is(std::string type) {
	return (type == "Sprite");
}