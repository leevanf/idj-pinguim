#ifndef PENGUINBODY
#define PENGUINBODY
#include "Component.h"
#include <memory>
class PenguinBody : public Component {
	private:
		std::weak_ptr<GameObject> pcannon;
		Vec2 speed;
		float linearSpeed;
		float angle;
		int hp;

		void _movePenguin();
	public:
		PenguinBody(GameObject& associated);
		~PenguinBody();
		void Start();
		virtual void Render();
		virtual void Update(float dt);
		virtual bool Is(std::string type) { return (type == "PenguinBody"); };
		virtual void NotifyCollision(GameObject& other);

		static PenguinBody* player;
};

#endif // PENGUINBODY