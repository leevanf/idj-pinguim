#ifndef SPRITE
#define SPRITE
#include "SDL.h"
#include "SDL_image.h"
#include <string>

class Sprite{
	private:
		SDL_Texture* texture;
		int width;
		int height;
		SDL_Rect clipRect;
	public:
		Sprite();
		Sprite(std::string file);
		~Sprite();
		void Open(std::string file);
		void SetClip(int x, int y, int w, int h);
		void Render(int x, int y);
		int GetWidth() { return width; }
		int GetHeight() { return height; }
		bool IsOpen() { return !!texture; }
};

#endif // SPRITE