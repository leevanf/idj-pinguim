#include "Alien.h"
#include "Bullet.h"
#include "Collider.h"
#include "PenguinBody.h"
#include "Sprite.h"
#include <iostream>

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, bool targetsPlayer, int frameCount, float frameTime) : Component(associated) {
	Sprite* bulletSprite = new Sprite(associated, sprite, Vec2(1,1), frameCount, frameTime);
	Collider* collider = new Collider(associated);
	associated.AddComponent(bulletSprite);
	associated.AddComponent(collider);
	distanceLeft = maxDistance;
	Bullet::targetsPlayer = targetsPlayer;
	Bullet::damage = damage;
	Bullet::speed = Vec2(1, 0).Rotate(angle).ScalarMultiply(speed);
	mAssociated.angleDeg = angle * 180 / M_PI;
}

void Bullet::Update(float dt) {
	float xMovement = speed.x * dt;
	float yMovement = speed.y * dt;
	distanceLeft -= Vec2(xMovement, yMovement).Magnitude();
	if (distanceLeft <= 0) {
		mAssociated.RequestDelete();
		return;
	}
	mAssociated.box.x += xMovement;
	mAssociated.box.y += yMovement;
}

void Bullet::Render() {

}

void Bullet::NotifyCollision(GameObject& other) {
	PenguinBody* player = (PenguinBody*)other.GetComponent("PenguinBody");
	Alien* alien = (Alien*)other.GetComponent("Alien");

	if (other.GetComponent("Bullet")) {
		return;
	}

	if (player && targetsPlayer) {
		mAssociated.RequestDelete();
	}

	if (alien && !targetsPlayer) {
		mAssociated.RequestDelete();
	}
}