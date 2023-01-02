#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(GameObject& associated, Vec2 scale, int frameCount, float frameTime, float secondsToSelfDestruct) : Component(associated) {
	texture = nullptr;
	width = 0;
	height = 0;
	Sprite::scale = scale;
	Sprite::frameCount = frameCount;
	Sprite::frameTime = frameTime;
	Sprite::secondsToSelfDestruct = secondsToSelfDestruct;
	currentFrame = 0;
	timeElapsed = 0;
}

Sprite::Sprite(GameObject& associated, std::string file, Vec2 scale, int frameCount, float frameTime, float secondsToSelfDestruct) : Sprite(associated, scale, frameCount, frameTime, secondsToSelfDestruct) {
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
	mAssociated.box.w = (float)(width / frameCount)*scale.x;
	mAssociated.box.h = (float)height*scale.y;
	SetFrame(0);
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::SetScaleX(float scaleX, float scaleY) {
	if (scaleX != 0) {
		mAssociated.box.w /= scale.x;
		scale.x = scaleX;
	}
	if (scaleY != 0) {
		mAssociated.box.h /= scale.y;
		scale.y = scaleY;
	}
	Vec2 associatedCenter = mAssociated.box.RectCenter();
	mAssociated.box.w *= scaleX;
	mAssociated.box.h *= scaleY;
	mAssociated.box.setRectCenter(associatedCenter);
}

void Sprite::Render() {
	Sprite::Render(mAssociated.box.x, mAssociated.box.y);
}

void Sprite::Render(float x, float y) {
	SDL_Rect dst;
	dst.x = (int)x + Camera::pos.x;
	dst.y = (int)y + Camera::pos.y;
	dst.w = clipRect.w * scale.x;
	dst.h = clipRect.h * scale.y;
	int renderCopyCode = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dst, mAssociated.angleDeg, nullptr, SDL_FLIP_NONE);
	if (renderCopyCode != 0) {
		std::cout << "SDL_RenderCopy failed: " << SDL_GetError() << "\n";
		exit(1);
	}
}

void Sprite::SetFrame(int frame) {
	currentFrame = frame;
	int frameSize = width / frameCount;
	Sprite::SetClip(currentFrame * frameSize, 0, frameSize, height);
	timeElapsed = 0;
}

void Sprite::SetFrameCount(int frameCount) { 
	currentFrame = 0;
	Sprite::frameCount = frameCount;
	mAssociated.box.w = (width / frameCount) * scale.x;
}

void Sprite::Update(float dt) {
	if (secondsToSelfDestruct > 0) {
		selfDestructCount.Update(dt);
		if (selfDestructCount.Get() > secondsToSelfDestruct) {
			mAssociated.RequestDelete();
		}
	}

	timeElapsed += dt;

	if (timeElapsed > frameTime) {
		if (currentFrame + 1 < frameCount) {
			SetFrame(currentFrame + 1);
		}
		else {
			SetFrame(0);
		}
	}
}

bool Sprite::Is(std::string type) {
	return (type == "Sprite");
}