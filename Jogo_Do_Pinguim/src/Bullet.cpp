#include "Bullet.h"
#include "Sprite.h"
#include <iostream>

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite) : Component(associated) {
	Sprite* bulletSprite = new Sprite(associated, sprite);
	associated.AddComponent(bulletSprite);
	distanceLeft = maxDistance;
	Bullet::damage = damage;
	Bullet::speed = Vec2(1, 0).Rotate(angle).ScalarMultiply(speed);
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

