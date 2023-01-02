#include "Bullet.h"
#include "Camera.h"
#include "Collider.h"
#include "Game.h"
#include "InputManager.h"
#include "PenguinCannon.h"
#include "Sprite.h"

#define CANNON_COOLDOWN 0.75

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated) {
	Sprite* penguinCannonSprite = new Sprite(associated, "..\\Jogo_Do_Pinguim\\img\\cubngun.png");
	Collider* collider = new Collider(associated);
	associated.AddComponent(penguinCannonSprite);
	associated.AddComponent(collider);
	pbody = penguinBody;
	angle = 0;
}

void PenguinCannon::Update(float dt) {
	cooldownTimer.Update(dt);
	Vec2 CANNON_OFFSET = Vec2(mAssociated.box.w / 2, 0).Rotate(angle);
	InputManager& inputManager = InputManager::GetInstance();
	if (pbody.expired()) {
		mAssociated.RequestDelete();
		return;
	}

	mAssociated.box.setRectCenter(pbody.lock()->box.RectCenter().x, pbody.lock()->box.RectCenter().y);
	Vec2 mousePos(inputManager.GetMouseX() - Camera::pos.x, inputManager.GetMouseY() - Camera::pos.y);
	angle = Vec2(mAssociated.box.RectCenter()).InclinationXAxisFromPoint(mousePos);
	mAssociated.angleDeg = angle * 180 / M_PI;
	if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
		PenguinCannon::Shoot();
	}
}

void PenguinCannon::Render() {

}

void PenguinCannon::Shoot() {
	if (cooldownTimer.Get() >= CANNON_COOLDOWN) {
		Vec2 CANNON_OFFSET = Vec2(mAssociated.box.w / 2, 0).Rotate(angle);
		GameObject* GO = new GameObject();
		Bullet* bullet = new Bullet(*GO, angle, 120, 15, 250, "..\\Jogo_Do_Pinguim\\img\\penguinbullet.png", false, 4, 0.04);
		GO->AddComponent(bullet);
		GO->box.setRectCenter(mAssociated.box.RectCenter() + CANNON_OFFSET);
		Game::GetInstance().GetState().AddObject(GO);
		cooldownTimer.Restart();
	}
}

void PenguinCannon::NotifyCollision(GameObject& other) {

}