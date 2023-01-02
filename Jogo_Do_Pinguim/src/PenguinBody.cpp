#include "Bullet.h"
#include "Camera.h"
#include "Collider.h"
#include "Game.h"
#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Sound.h"
#include "Sprite.h"
#include "State.h"

PenguinBody* PenguinBody::player;
PenguinBody::PenguinBody(GameObject& associated) : Component(associated) {
	Sprite* penguinBodySprite = new Sprite(associated, "..\\Jogo_Do_Pinguim\\img\\penguin.png");
	Collider* collider = new Collider(associated);
	associated.AddComponent(penguinBodySprite);
	associated.AddComponent(collider);
	speed = Vec2(0, 0);
	linearSpeed = 0;
	angle = 0;
	hp = 100;
	player = this;
}

PenguinBody::~PenguinBody() {
	player = nullptr;
}

void PenguinBody::Start() {
	State& state = Game::GetInstance().GetState();
	GameObject* GO = new GameObject();
	PenguinCannon* penguinCannon = new PenguinCannon(*GO, state.GetObjectPtr(&mAssociated));
	GO->AddComponent(penguinCannon);
	pcannon = state.AddObject(GO);
}

void PenguinBody::Update(float dt) {
	float acceleration = 1.5;
	InputManager& inputManager = InputManager::GetInstance();
	int angularVelocity = 65 * dt;
	if (inputManager.IsKeyDown(A_KEY)) {
		mAssociated.angleDeg = fmod(mAssociated.angleDeg - angularVelocity, 360);
		angle = mAssociated.angleDeg;
	}
	if (inputManager.IsKeyDown(D_KEY)) {
		mAssociated.angleDeg = fmod(mAssociated.angleDeg + angularVelocity, 360);
		angle = mAssociated.angleDeg;
	}
	if (inputManager.IsKeyDown(W_KEY)) {
		float MAX_FWD_VELOCITY = 5;
		linearSpeed += acceleration * dt;
		if (linearSpeed > MAX_FWD_VELOCITY) linearSpeed = MAX_FWD_VELOCITY;
		speed = Vec2(1, 0).RotateDeg(angle).Normalize().ScalarMultiply(linearSpeed);
		PenguinBody::_movePenguin();
	}
	if (inputManager.IsKeyDown(S_KEY)) {
		float MAX_BWD_VELOCITY = -3;
		linearSpeed -= acceleration * dt;
		if (linearSpeed < MAX_BWD_VELOCITY) linearSpeed = MAX_BWD_VELOCITY;
		speed = Vec2(1, 0).RotateDeg(angle).Normalize().ScalarMultiply(linearSpeed);
		PenguinBody::_movePenguin();
	}
	if (!inputManager.IsKeyDown(W_KEY) && !inputManager.IsKeyDown(S_KEY)) {
		linearSpeed -= copysign(acceleration / 2 * dt, linearSpeed);
		speed.Subtract(Vec2(speed.x * acceleration / 2 * dt, speed.y * acceleration / 2 * dt));
		PenguinBody::_movePenguin();
	}
	if (hp <= 0) {
		mAssociated.RequestDelete();
		GameObject* GO = new GameObject();
		Sprite* deathSprite = new Sprite(*GO, "..\\Jogo_Do_Pinguim\\img\\penguindeath.png", Vec2(1,1), 5, 0.15, 0.75);
		GO->box.setRectCenter(mAssociated.box.RectCenter());
		GO->AddComponent(deathSprite);
		Sound* deathSound = new Sound(*GO, "..\\Jogo_Do_Pinguim\\audio\\boom2.wav");
		deathSound->Play();
		GO->AddComponent(deathSound);
		Game::GetInstance().GetState().AddObject(GO);
	}
}

void PenguinBody::_movePenguin() {
	Vec2 penguinPos(this->mAssociated.box.x, this->mAssociated.box.y);
	penguinPos.Add(speed);
	this->mAssociated.box.x = penguinPos.x;
	this->mAssociated.box.y = penguinPos.y;
}

void PenguinBody::Render() {

}

void PenguinBody::NotifyCollision(GameObject& other) {
	Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
	if (bullet && bullet->targetsPlayer) {
		hp -= bullet->GetDamage();
	}
	if (hp <= 0) {
		Camera::Unfollow();
	}
}