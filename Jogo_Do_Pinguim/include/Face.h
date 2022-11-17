#ifndef FACE
#define FACE
#include "Component.h"
#include <string>
class Face : public Component{
	private:
		int hitpoints;
	public:
		Face(GameObject& associated);
		void Damage(int damage);
		virtual void Update(float dt);
		virtual void Render();
		virtual bool Is(std::string type);
};

#endif // FACE