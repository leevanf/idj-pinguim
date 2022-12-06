#include "Face.h"
#include "Sound.h"
#include "Camera.h"
#include "InputManager.h"

Face::Face(GameObject& associated) : Component(associated) {
	hitpoints = 30;
}

void Face::Damage(int damage) {
	hitpoints -= damage;
	if (hitpoints <= 0) {
		mAssociated.RequestDelete();
		Sound* soundComponent = ((Sound*)mAssociated.GetComponent("Sound"));
		if (soundComponent) soundComponent->Play();
	}
}

void Face::Update(float dt) {
	InputManager& inputManager = InputManager::GetInstance();
	if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
		if (mAssociated.box.isPointInsideRect((float)inputManager.GetMouseX()-Camera::pos.x, (float)inputManager.GetMouseY()-Camera::pos.y)) {
			Damage(std::rand() % 10 + 10);
		}
	}
}

void Face::Render() {

}

bool Face::Is(std::string type) {
	return type == "Face";
}