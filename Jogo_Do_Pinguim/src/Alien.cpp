#include "Alien.h"
#include "Bullet.h"
#include "Camera.h"
#include "Collider.h"
#include "Game.h"
#include "Minion.h"
#include "PenguinBody.h"
#include "Sound.h"
#include "Sprite.h"
#include "State.h"
#include "InputManager.h"
#include "SDL.h"
#include <iostream>
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define MOVE_COOLDOWN 1.5

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
	Sprite* alienSprite = new Sprite(associated, "..\\Jogo_Do_Pinguim\\img\\alien.png");
	Collider* collider = new Collider(associated,Vec2(0.7,0.6));
	associated.AddComponent(alienSprite);
	associated.AddComponent(collider);
	speed = Vec2();
	hp = 100;
	alienCount++;
}

Alien::~Alien() {
	minionArray.clear();
	alienCount--;
}

void Alien::Start() {
	State& state = Game::GetInstance().GetState();
	int MINION_QUANTITY = 3;
	for (int counter = 0; counter < MINION_QUANTITY; counter++) {
		GameObject* GO = new GameObject();
		Minion* minion = new Minion(*GO, state.GetObjectPtr(&mAssociated), counter * 360 / MINION_QUANTITY);
		GO->AddComponent(minion);
		minionArray.push_back(state.AddObject(GO));
	}
}

int Alien::_moveAlien(Vec2 velVector, Vec2 alienPos, Vec2 playerPos) {
	int counter = 0;
	switch (alienPos.x < playerPos.x) {
	case true:
		if (alienPos.x + velVector.x >= playerPos.x) {
			mAssociated.box.setRectCenterX(playerPos.x);
			counter++;
		}
		else {
			mAssociated.box.setRectCenterX(alienPos.x + velVector.x);
		}
		break;
	case false:
		if (alienPos.x + velVector.x <= playerPos.x) {
			mAssociated.box.setRectCenterX(playerPos.x);
			counter++;
		}
		else {
			mAssociated.box.setRectCenterX(alienPos.x + velVector.x);
		}
		break;
	}

	switch (alienPos.y < playerPos.y) {
	case true:
		if (alienPos.y + velVector.y >= playerPos.y) {
			mAssociated.box.setRectCenterY(playerPos.y);
			counter++;
		}
		else {
			mAssociated.box.setRectCenterY(alienPos.y + velVector.y);
		}
		break;
	case false:
		if (alienPos.y + velVector.y <= playerPos.y) {
			mAssociated.box.setRectCenterY(playerPos.y);
			counter++;
		}
		else {
			mAssociated.box.setRectCenterY(alienPos.y + velVector.y);
		}
		break;
	}

	return counter;
}

void Alien::PlayDeathAnimation() {
	GameObject* GO = new GameObject();
	Sprite* deathSprite = new Sprite(*GO, "..\\Jogo_Do_Pinguim\\img\\aliendeath.png", Vec2(0.8, 0.8), 4, 0.2, 0.8);
	GO->box.setRectCenter(mAssociated.box.RectCenter());
	GO->AddComponent(deathSprite);
	Sound* deathSound = new Sound(*GO, "..\\Jogo_Do_Pinguim\\audio\\boom2.wav");
	deathSound->Play();
	GO->AddComponent(deathSound);
	Game::GetInstance().GetState().AddObject(GO);
}

void Alien::Update(float dt) {
	State& gameState = Game::GetInstance().GetState();
	mAssociated.angleDeg -= 5*dt;

	if (state == Alien::AlienState::RESTING) {
		Alien::restTimer.Update(dt);
		if (Alien::restTimer.Get() >= MOVE_COOLDOWN) {
			if (PenguinBody::player) {
				destination = PenguinBody::player->GetPlayerPos();
				state = Alien::AlienState::MOVING;
			}
		}
	}
	else if (state == Alien::AlienState::MOVING) {
		Vec2 playerPos;
		if (PenguinBody::player) playerPos = PenguinBody::player->GetPlayerPos();
		int velocity = 100;
		Vec2 alienPos(this->mAssociated.box.x, this->mAssociated.box.y);
		Vec2 velVector = (destination - mAssociated.box.RectCenter()).Normalize().ScalarMultiply(velocity * dt);
		int movCode = Alien::_moveAlien(velVector, mAssociated.box.RectCenter(), destination);

		if (movCode == 2) {
			int index = 0;
			float baseMag = std::numeric_limits<float>::infinity();
			float tempMag = 0;
			for (int counter = 0; counter < minionArray.size(); ++counter) {
				tempMag = (minionArray[counter].lock()->box.RectCenter() - playerPos).Magnitude();
				if (tempMag < baseMag) {
					index = counter;
					baseMag = tempMag;
				}
			}
			Minion* minion = (Minion*)minionArray[index].lock()->GetComponent("Minion");
			minion->Shoot(playerPos);
			state = Alien::AlienState::RESTING;
			Alien::restTimer.Restart();
		}
	}

	if (this->hp <= 0) {
		mAssociated.RequestDelete();
		Alien::PlayDeathAnimation();
	}
}

void Alien::Render() {

}

void Alien::NotifyCollision(GameObject& other) {
	Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
	if (bullet && !bullet->targetsPlayer) {
		hp -= bullet->GetDamage();
	}
}