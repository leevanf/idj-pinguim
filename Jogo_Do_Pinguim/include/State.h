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
		bool started;

		std::vector<std::shared_ptr<GameObject>> objectArray;
	public:
		State();
		~State();
		void LoadAssets();
		void Start();
		void Update(float dt);
		void Render();
		bool QuitRequested() { return quitRequested; }

		std::weak_ptr<GameObject> AddObject(GameObject* go);
		std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
};

#endif // STATE