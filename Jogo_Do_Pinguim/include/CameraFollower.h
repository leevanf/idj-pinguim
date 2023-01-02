#ifndef CAMERAFOLLOWER
#define CAMERAFOLLOWER
#include "Component.h"
#include "GameObject.h"

class CameraFollower : public Component{
	public:
		CameraFollower(GameObject& go);
		virtual void Update(float dt);
		virtual void Render();
		virtual bool Is(std::string type);
		virtual void NotifyCollision(GameObject& other) {};
};

#endif //CAMERAFOLLOWER 