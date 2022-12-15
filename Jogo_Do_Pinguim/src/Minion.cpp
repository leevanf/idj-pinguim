#include <cmath>
#include <iostream>
#include "Bullet.h"
#include "Game.h"
#include "Minion.h"
#include "Sprite.h"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(alienCenter){
	Sprite* minionSprite = new Sprite(associated, "..\\Jogo_Do_Pinguim\\img\\minion.png");
	associated.AddComponent(minionSprite);
	arc = arcOffsetDeg;
	Minion::Update(0.03);
}

void Minion::Update(float dt) {
	if (alienCenter.expired()) {
		mAssociated.RequestDelete();
		return;
	}
	GameObject* alien = alienCenter.lock().get();
	float angularVelocity = M_PI / 2;
	Vec2 initialDistance(100,100);
	initialDistance.Rotate(Minion::arc).Add(Vec2(alien->box.RectCenter().x, alien->box.RectCenter().y));
	mAssociated.box.setRectCenter(initialDistance.x, initialDistance.y);
	arc += angularVelocity*dt;
}

void Minion::Render() {

}

void Minion::Shoot(Vec2 pos) {
	GameObject* GO = new GameObject();
	Vec2 shootVector = pos - mAssociated.box.RectCenter();
	Bullet* bullet = new Bullet(*GO, shootVector.InclinationXAxis(), 100, 10, 250, "..\\Jogo_Do_Pinguim\\img\\minionbullet1.png");
	GO->AddComponent(bullet);
	GO->box.x = mAssociated.box.x;
	GO->box.y = mAssociated.box.y;
	Game::GetInstance().GetState().AddObject(GO);
}