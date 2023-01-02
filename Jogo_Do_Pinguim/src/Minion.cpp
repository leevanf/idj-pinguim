#include <cmath>
#include <iostream>
#include "Bullet.h"
#include "Collider.h"
#include "Game.h"
#include "Minion.h"
#include "Sprite.h"
#include "Alien.h"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(alienCenter){
	float minionScale = 1 + (rand()) / (RAND_MAX / (0.5));
	Sprite* minionSprite = new Sprite(associated, "..\\Jogo_Do_Pinguim\\img\\minion.png", Vec2(minionScale,minionScale));
	Collider* collider = new Collider(associated);
	associated.AddComponent(minionSprite);
	associated.AddComponent(collider);
	int angulo = 0;
	arc = arcOffsetDeg;
	mAssociated.angleDeg = arcOffsetDeg+120;
	Minion::Update(0.03);
}

void Minion::Update(float dt) {
	if (alienCenter.expired()) {
		mAssociated.RequestDelete();
		return;
	}
	GameObject* alien = alienCenter.lock().get();
	float angularVelocity = 90;
	mAssociated.angleDeg = fmod(mAssociated.angleDeg + angularVelocity * dt, 360);
	Vec2 initialDistance(120,70);
	initialDistance.RotateDeg(Minion::arc).Add(Vec2(alien->box.RectCenter().x, alien->box.RectCenter().y));
	mAssociated.box.setRectCenter(initialDistance.x, initialDistance.y);
	arc += angularVelocity*dt;
}

void Minion::Render() {

}

void Minion::Shoot(Vec2 pos) {
	GameObject* GO = new GameObject();
	Vec2 shootVector = pos - mAssociated.box.RectCenter();
	Bullet* bullet = new Bullet(*GO, shootVector.InclinationXAxis(), 100, 10, 250, "..\\Jogo_Do_Pinguim\\img\\minionbullet2.png", true, 3, 0.04);
	GO->AddComponent(bullet);
	GO->box.x = mAssociated.box.RectCenter().x;
	GO->box.y = mAssociated.box.RectCenter().y;
	Game::GetInstance().GetState().AddObject(GO);
}

void Minion::NotifyCollision(GameObject& other) {

}