#ifndef SPRITE
#define SPRITE
#include "SDL.h"
#include "SDL_image.h"
#include "GameObject.h"
#include <string>

class Sprite : public Component{
	private:
		SDL_Texture* texture;
		int width;
		int height;
		SDL_Rect clipRect;
		Vec2 scale;
	public:
		Sprite(GameObject& associated, Vec2 scale = Vec2(1, 1));
		Sprite(GameObject& associated, std::string file, Vec2 scale = Vec2(1, 1));
		virtual ~Sprite();
		void Open(std::string file);
		void SetClip(int x, int y, int w, int h);
		void SetScaleX(float scaleX, float scaleY);
		virtual void Render();
		void Render(float x, float y);
		virtual void Update(float dt);
		virtual bool Is(std::string type);
		int GetWidth() { return width * scale.x; }
		int GetHeight() { return height * scale.y; }
		bool IsOpen() { return !!texture; }
		Vec2 GetScale() { return scale; }
};

#endif // SPRITE