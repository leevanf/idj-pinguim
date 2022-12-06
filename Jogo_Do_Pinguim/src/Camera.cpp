#include "Camera.h"
#include "InputManager.h"
#include "SDL.h"
GameObject* Camera::focus;
Vec2 Camera::pos;
Vec2 Camera::speed;

void Camera::Follow(GameObject* newFocus) {
	focus = newFocus;
}

void Camera::Unfollow() {
	focus = nullptr;
}

void Camera::Update(float dt) {
	int cameraSpeed = 150;
	if (focus) {
		pos = Vec2(focus->box.x, focus->box.y);
	}
	else {
		InputManager& inputManager = InputManager::GetInstance();
		speed = Vec2();
		if (inputManager.IsKeyDown(UP_ARROW_KEY)) {
			speed = Vec2(0, cameraSpeed) + speed;
		}
		if (inputManager.IsKeyDown(DOWN_ARROW_KEY)) {
			speed = Vec2(0, -cameraSpeed) + speed;
		}
		if (inputManager.IsKeyDown(RIGHT_ARROW_KEY)) {
			speed = Vec2(-cameraSpeed, 0) + speed;
		}
		if (inputManager.IsKeyDown(LEFT_ARROW_KEY)) {
			speed = Vec2(cameraSpeed, 0) + speed;
		}
		pos = (speed*dt) + pos;
	}
}