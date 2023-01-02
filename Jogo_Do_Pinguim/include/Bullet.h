#ifndef BULLET
#define BULLET
#include "Component.h"
class Bullet : public Component {
	private:
		Vec2 speed;
		float distanceLeft;
		int damage;
	public:
		Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, bool targetsPlayer, int frameCount = 1, float frameTime = 1);
		virtual void Update(float dt);
		virtual void Render();
		virtual bool Is(std::string type) { return (type == "Bullet"); };
		virtual void NotifyCollision(GameObject& other);
		int GetDamage() { return damage; };
		bool targetsPlayer;
};

#endif // BULLET