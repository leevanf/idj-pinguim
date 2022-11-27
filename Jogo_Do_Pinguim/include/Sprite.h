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
	public:
		Sprite(GameObject& associated);
		Sprite(GameObject& associated, std::string file);
		virtual ~Sprite();
		void Open(std::string file);
		void SetClip(int x, int y, int w, int h);
		virtual void Render();
		void Render(float x, float y);
		virtual void Update(float dt);
		virtual bool Is(std::string type);
		int GetWidth() { return width; }
		int GetHeight() { return height; }
		bool IsOpen() { return !!texture; }
};

#endif // SPRITE