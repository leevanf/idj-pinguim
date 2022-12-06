#ifndef GAME
#define GAME
//#define INCLUDE_SDL
//#define INCLUDE_SDL_IMAGE
//#define INCLUDE_SDL_MIXER
//#include "SDL_include.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>
#include "State.h"
#include "InputManager.h"

class Game{
	private:
		static Game* instance;
		SDL_Window* window;
		SDL_Renderer* renderer;
		State* state;
		int frameStart;
		float dt;
		void CalculateDeltaTime();

		Game(std::string title, int width, int height);
	public:
		~Game();
		void Run();
		SDL_Renderer* GetRenderer() { return renderer; }
		State& GetState() { return *state; }
		static Game& GetInstance();
		float GetDeltaTime() { return dt; };
};

#endif // GAME