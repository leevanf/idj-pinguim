#ifndef GAMEOBJECT
#define GAMEOBJECT
class GameObject;
#include "Component.h"
#include "Rect.h"
#include <vector>
#include <string>

class GameObject{
	private:
		std::vector<Component*> components;
		bool isDead;
	public:
		GameObject();
		~GameObject();
		void Start();
		void Update(float dt);
		void Render();
		bool IsDead();
		void RequestDelete();
		void NotifyCollision(GameObject& other);
		void AddComponent(Component* cpt);
		void RemoveComponent(Component* cpt);
		Component* GetComponent(std::string type);
		Rect box;
		bool started;
		double angleDeg;
};

#endif //GAMEOBJECT

