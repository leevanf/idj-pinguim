#ifndef MINION
#define MINION
#include "Component.h"
#include <memory>

class Minion : public Component {
	private:
		std::weak_ptr<GameObject> alienCenter;
		float arc;
	public:
		Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
		void Shoot(Vec2 target);
		virtual void Update(float dt);
		virtual void Render();
		virtual bool Is(std::string type) { return (type == "Minion"); };
};

#endif // MINION