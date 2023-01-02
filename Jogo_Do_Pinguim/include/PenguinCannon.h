#ifndef PENGUINCANNON
#define PENGUINCANNON
#include "Component.h"
#include "Timer.h"
#include <memory>
class PenguinCannon : public Component {
	private:
		std::weak_ptr<GameObject> pbody;
		float angle;
	public:
		PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
		virtual void Render();
		virtual void Update(float dt);
		virtual bool Is(std::string type) { return (type == "PenguinCannon"); };
		virtual void NotifyCollision(GameObject& other);
		void Shoot();
		Timer cooldownTimer;
};

#endif // PENGUINCANNON