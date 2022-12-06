#ifndef INPUTMANAGER
#define INPUTMANAGER
#include "SDL.h"
#include <unordered_map>
#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define SPACEBAR_KEY SDLK_SPACE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT

class InputManager{
	private:
		bool mouseState[6] = {};
		int mouseUpdate[6] = {};
		std::unordered_map<int, bool> keyState;
		std::unordered_map<int, int> keyUpdate;
		bool quitRequested;
		int updateCounter;
		int mouseX;
		int mouseY;
		InputManager();
		~InputManager();
	public:
		static InputManager& GetInstance() {
			static InputManager instance;
			return instance;
		};
		void Update();
		bool KeyPress(int key);
		bool KeyRelease(int key);
		bool IsKeyDown(int key);
		bool MousePress(int button);
		bool MouseRelease(int button);
		bool IsMouseDown(int button);
		int GetMouseX() { return mouseX; };
		int GetMouseY() { return mouseY; };
		bool QuitRequested() { return quitRequested; };
};

#endif // INPUTMANAGER