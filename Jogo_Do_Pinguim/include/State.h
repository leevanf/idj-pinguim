#ifndef STATE
#define STATE
#include "SDL.h"
#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include "TileSet.h"
#include <vector>

class State{
	private:
		Music music;
		bool quitRequested;
		TileSet* tileSet;

		std::vector<std::unique_ptr<GameObject>> objectArray;
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