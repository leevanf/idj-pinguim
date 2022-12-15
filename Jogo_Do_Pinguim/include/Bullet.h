#ifndef BULLET
#define BULLET
#include "Component.h"
class Bullet : public Component {
	private:
		Vec2 speed;
		float distanceLeft;
		int damage;
	public:
		Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite);
		virtual void Update(float dt);
		virtual void Render();
		virtual bool Is(std::string type) { return (type == "Bullet"); };
		int GetDamage() { return damage; };
};

#endif // BULLET