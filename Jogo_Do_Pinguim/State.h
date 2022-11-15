#ifndef STATE
#define STATE
#include "SDL.h"
#include "Sprite.h"
#include "Music.h"

class State{
	private:
		Sprite bg;
		Music music;
		bool quitRequested;
	public:
		State();
		void LoadAssets();
		void Update(float dt);
		void Render();
		bool QuitRequested() { return quitRequested; }
};

#endif // STATE