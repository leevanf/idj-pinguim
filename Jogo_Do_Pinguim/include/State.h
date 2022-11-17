#ifndef STATE
#define STATE
#include "SDL.h"
#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include <vector>

class State{
	private:
		Music music;
		bool quitRequested;

		std::vector<std::unique_ptr<GameObject>> objectArray;
		void Input();
		void AddObject(int mouseX, int mouseY);
	public:
		State();
		~State();
		void LoadAssets();
		void Update(float dt);
		void Render();
		bool QuitRequested() { return quitRequested; }

};

#endif // STATE