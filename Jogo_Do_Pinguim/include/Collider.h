#ifndef COLLIDER
#define COLLIDER
#include "Component.h"
#include "Vec2.h"
class Collider : public Component {
	private:
		Vec2 scale;
		Vec2 offset;
	public:
		Collider(GameObject& associated, Vec2 scale = Vec2(1, 1), Vec2 offset = Vec2(0, 0));
		Rect box;
		virtual void Update(float dt);
		virtual void Render();
		virtual bool Is(std::string type) { return (type == "Collider"); };
		virtual void NotifyCollision(GameObject& other) {};
		void SetScale(Vec2 scale) { Collider::scale = scale; };
		void SetOffset(Vec2 offset) { Collider::offset = offset; };
		GameObject* getGameObject() { GameObject* pointer = &mAssociated; return pointer; };
};

#endif //COLLIDER