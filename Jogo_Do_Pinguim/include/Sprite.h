#ifndef SPRITE
#define SPRITE
#include "SDL.h"
#include "SDL_image.h"
#include "GameObject.h"
#include "Timer.h"
#include <string>

class Sprite : public Component{
	private:
		SDL_Texture* texture;
		int width;
		int height;
		SDL_Rect clipRect;
		Vec2 scale;
		int frameCount;
		int currentFrame;
		float timeElapsed;
		float frameTime;
		float secondsToSelfDestruct = 0;
		Timer selfDestructCount;
	public:
		Sprite(GameObject& associated, Vec2 scale = Vec2(1, 1), int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);
		Sprite(GameObject& associated, std::string file, Vec2 scale = Vec2(1, 1), int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);
		virtual ~Sprite();
		void Open(std::string file);
		void SetClip(int x, int y, int w, int h);
		void SetScaleX(float scaleX, float scaleY);
		virtual void Render();
		void Render(float x, float y);
		virtual void Update(float dt);
		virtual bool Is(std::string type);
		virtual void NotifyCollision(GameObject& other) {};
		void SetFrame(int frame);
		void SetFrameCount(int frameCount);
		void SetFrameTime(int frameTime) { Sprite::frameTime = frameTime; };
		int GetWidth() { return (width / frameCount) * scale.x; }
		int GetHeight() { return height * scale.y; }
		bool IsOpen() { return !!texture; }
		Vec2 GetScale() { return scale; }
};

#endif // SPRITE