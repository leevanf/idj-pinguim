#ifndef ALIEN
#define ALIEN
#include "Vec2.h"
#include "Component.h"
#include "Timer.h"
#include <queue>
#include <memory>

class Alien : public Component {
	private:
		Vec2 speed;
		int hp;
		std::vector<std::weak_ptr<GameObject>> minionArray;
		enum AlienState { MOVING, RESTING };
		AlienState state = RESTING;
		Timer restTimer;
		Vec2 destination;
		int _moveAlien(Vec2 velVector, Vec2 alienPos, Vec2 playerPos);
		void PlayDeathAnimation();
	public:
		Alien(GameObject& associated, int nMinions);
		~Alien();
		virtual void Start();
		virtual void Update(float dt);
		virtual void Render();
		virtual void NotifyCollision(GameObject& other);
		virtual bool Is(std::string type) { return (type == "Alien"); };
		static int alienCount;
};

#endif //ALIEN