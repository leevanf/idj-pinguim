#define _USE_MATH_DEFINES
#include <cmath>
#include "State.h"
#include "Face.h"
#include "Sound.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"

State::State() : music{ "..\\Jogo_Do_Pinguim\\audio\\stageState.ogg" } {
	started = false;
	quitRequested = false;

	GameObject* GO = new GameObject();
	Sprite* background = new Sprite(*GO, "..\\Jogo_Do_Pinguim\\img\\ocean.jpg");
	CameraFollower* camFollower = new CameraFollower(*GO);
	GO->box.x = 0;
	GO->box.y = 0;
	GO->AddComponent(background);
	GO->AddComponent(camFollower);
	objectArray.emplace_back(GO);

	GameObject* GO2 = new GameObject();
	tileSet = new TileSet(64,64, "..\\Jogo_Do_Pinguim\\img\\tileset.png");
	TileMap* tileMap = new TileMap(*GO2, "..\\Jogo_Do_Pinguim\\map\\tilemap.txt", tileSet);
	GO2->box.x = 0;
	GO2->box.y = 0;
	GO2->AddComponent(tileMap);
	objectArray.emplace_back(GO2);

	GameObject* GO3 = new GameObject();
	Alien* alien = new Alien(*GO3, 0);
	GO3->box.setRectCenter(512, 300);
	GO3->AddComponent(alien);
	objectArray.emplace_back(GO3);

	music.Play();
}

State::~State() {
	delete tileSet;
	objectArray.clear();
}

void State::Start() {
	State::LoadAssets();
	for (int counter = 0; counter < objectArray.size(); counter++) {
		objectArray[counter]->Start();
	}
	started = true;
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
	std::shared_ptr<GameObject> GO(go);
	objectArray.push_back(GO);
	if (started) {
		GO->Start();
	}
	return std::weak_ptr<GameObject>(GO);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
	for (auto it = objectArray.begin(); it != objectArray.end(); ++it) {
		if (it->get() == go) {
			return std::weak_ptr<GameObject>(*it);
		}
	}
	return std::weak_ptr<GameObject>();
}

void State::LoadAssets() {
	// pre carrega os assets do state do jogo
}

void State::Update(float dt) {
	InputManager& inputManager = InputManager::GetInstance();
	Camera::Update(dt);
	if (inputManager.QuitRequested() || inputManager.IsKeyDown(ESCAPE_KEY)) {
		quitRequested = true;
	}
	for (int counter = 0; counter < objectArray.size(); counter++) {
		objectArray[counter]->Update(dt);
	}
	for (int counter = 0; counter < objectArray.size(); counter++) {
		if (objectArray[counter]->IsDead()) {
			objectArray.erase(objectArray.begin() + counter);
		}
	}
}

void State::Render() {
	for (auto it = objectArray.begin(); it != objectArray.end(); ++it) {
		(*it)->Render();
	}
}