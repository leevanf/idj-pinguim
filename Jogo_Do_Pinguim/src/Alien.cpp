#include "Alien.h"
#include "Camera.h"
#include "Game.h"
#include "Minion.h"
#include "State.h"
#include "Sprite.h"
#include "InputManager.h"
#include "SDL.h"
#include <iostream>
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
	Sprite* alienSprite = new Sprite(associated, "..\\Jogo_Do_Pinguim\\img\\alien.png");
	associated.AddComponent(alienSprite);
	speed = Vec2();
	hp = 100;
}

Alien::~Alien() {
	minionArray.clear();
}

void Alien::Start() {
	State& state = Game::GetInstance().GetState();
	for (int counter = 0; counter < 3; counter++) {
		GameObject* GO = new GameObject();
		Minion* minion = new Minion(*GO, state.GetObjectPtr(&mAssociated), counter * 120);
		GO->AddComponent(minion);
		minionArray.push_back(state.AddObject(GO));
	}
}

void Alien::_moveAlien(Vec2 velVector, Vec2 alienPos, Vec2 mousePos) {
	int counter = 0;
	switch (alienPos.x < mousePos.x) {
	case true:
		if (alienPos.x + velVector.x >= mousePos.x) {
			this->mAssociated.box.x = mousePos.x;
			counter++;
		}
		else {
			this->mAssociated.box.x = alienPos.x + velVector.x;
		}
		break;
	case false:
		if (alienPos.x + velVector.x <= mousePos.x) {
			this->mAssociated.box.x = mousePos.x;
			counter++;
		}
		else {
			this->mAssociated.box.x = alienPos.x + velVector.x;
		}
		break;
	}

	switch (alienPos.y < mousePos.y) {
	case true:
		if (alienPos.y + velVector.y >= mousePos.y) {
			this->mAssociated.box.y = mousePos.y;
			counter++;
		}
		else {
			this->mAssociated.box.y = alienPos.y + velVector.y;
		}
		break;
	case false:
		if (alienPos.y + velVector.y <= mousePos.y) {
			this->mAssociated.box.y = mousePos.y;
			counter++;
		}
		else {
			this->mAssociated.box.y = alienPos.y + velVector.y;
		}
		break;
	}

	if (counter == 2) {
		taskQueue.pop();
	}
}

void Alien::Update(float dt) {
	State& state = Game::GetInstance().GetState();
	InputManager& inputManager = InputManager::GetInstance();
	mAssociated.angleDeg -= 5*dt;
	if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
		Action action(Action::ActionType::SHOOT, Vec2(inputManager.GetMouseX() - Camera::pos.x, inputManager.GetMouseY() - Camera::pos.y));
		taskQueue.emplace(action);
	}
	if (inputManager.MousePress(RIGHT_MOUSE_BUTTON)) {
		Action action(Action::ActionType::MOVE, Vec2(inputManager.GetMouseX() - Camera::pos.x, inputManager.GetMouseY() - Camera::pos.y));
		taskQueue.emplace(action);
	}
	std::cout << taskQueue.size() << "\n";
	if (taskQueue.size() > 0) {
		if (taskQueue.size() != 0 && taskQueue.front().type == Action::ActionType::SHOOT) {
			int index = 0;
			float baseMag = std::numeric_limits<float>::infinity();
			float tempMag = 0;
			for (int counter = 0; counter < minionArray.size(); ++counter) {
				tempMag = (minionArray[counter].lock()->box.RectCenter() - taskQueue.front().pos).Magnitude();
				if (tempMag < baseMag) {
					index = counter;
					baseMag = tempMag;
				}
			}
			Minion* minion = (Minion*)minionArray[index].lock()->GetComponent("Minion");
			minion->Shoot(taskQueue.front().pos);
			taskQueue.pop();
		}
		if (taskQueue.size() != 0 && taskQueue.front().type == Action::ActionType::MOVE) {
			int velocity = 150;
			Vec2 alienPos(this->mAssociated.box.x, this->mAssociated.box.y);
			Vec2 mousePos = taskQueue.front().pos - Vec2(mAssociated.box.w / 2, mAssociated.box.h / 2);
			Vec2 velVector = (mousePos - alienPos).Normalize().ScalarMultiply(velocity*dt);
			Alien::_moveAlien(velVector, alienPos, mousePos);
		}
	}
	if (this->hp <= 0) {
		mAssociated.RequestDelete();
	}
}

void Alien::Render() {

}

Action::Action(ActionType type, float x, float y) {
	Action::type = type;
	Action::pos = Vec2(x, y);
}

Action::Action(ActionType type, Vec2 coord) {
	Action::type = type;
	Action::pos = coord;
}