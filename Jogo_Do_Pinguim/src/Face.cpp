#include "Face.h"
#include "Sound.h"

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

}

void Face::Render() {

}

bool Face::Is(std::string type) {
	return type == "Face";
}