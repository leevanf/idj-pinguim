#ifndef COMPONENT
#define COMPONENT
#include <string>
class Component;
#include "GameObject.h"

class Component{
	protected:
		GameObject& mAssociated;
	public:
		Component(GameObject& associated);
		virtual ~Component() {};
		virtual void Update(float dt) = 0;
		virtual void Render() = 0;
		virtual bool Is(std::string type) = 0;
};

#endif // COMPONENT
