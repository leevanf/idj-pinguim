#ifndef ALIEN
#define ALIEN
#include "Vec2.h"
#include "Component.h"
#include <queue>
#include <memory>

class Action {
	public:
		enum ActionType {
			MOVE,
			SHOOT,
		};

		Action(ActionType type, float x, float y);
		Action(ActionType type, Vec2 coord);
		ActionType type;
		Vec2 pos;
};

class Alien : public Component {
	private:
		Vec2 speed;
		int hp;
		std::queue<Action> taskQueue;
		std::vector<std::weak_ptr<GameObject>> minionArray;

		void _moveAlien(Vec2 velVector, Vec2 alienPos, Vec2 mousePos);
	public:
		Alien(GameObject& associated, int nMinions);
		~Alien();
		virtual void Start();
		virtual void Update(float dt);
		virtual void Render();
		virtual bool Is(std::string type) { return (type == "Alien"); };

};

#endif //ALIEN