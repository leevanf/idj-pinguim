#define _USE_MATH_DEFINES
#include <cmath>
#include "State.h"
#include "Face.h"
#include "Sound.h"
#include "TileMap.h"

State::State() : music{ "..\\Jogo_Do_Pinguim\\audio\\stageState.ogg" } {
	GameObject* GO = new GameObject();
	Sprite* background = new Sprite(*GO, "..\\Jogo_Do_Pinguim\\img\\ocean.jpg");
	GO->box.x = 0;
	GO->box.y = 0;
	GO->AddComponent(background);
	objectArray.emplace_back(GO);

	GameObject* GO2 = new GameObject();
	tileSet = new TileSet(64,64, "..\\Jogo_Do_Pinguim\\img\\tileset.png");
	TileMap* tileMap = new TileMap(*GO2, "..\\Jogo_Do_Pinguim\\map\\tilemap.txt", tileSet);
	GO2->box.x = 0;
	GO2->box.y = 0;
	GO2->AddComponent(tileMap);
	objectArray.emplace_back(GO2);

	quitRequested = false;
	music.Play();
}

State::~State() {
	delete tileSet;
	objectArray.clear();
}

void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if (event.type == SDL_QUIT) {
			quitRequested = true;
		}

		// Se o evento for clique...
		if (event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for (int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*)objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if (go->box.isPointInsideRect((float)mouseX, (float)mouseY)) {
					Face* face = (Face*)go->GetComponent("Face");
					if (nullptr != face) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if (event.type == SDL_KEYDOWN) {
			// Se a tecla for ESC, setar a flag de quit
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2(200, 0).Rotate(-M_PI + M_PI * (rand() % 1001) / 500.0).Add(Vec2(mouseX, mouseY));
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

void State::AddObject(int mouseX, int mouseY) {
	GameObject* GO = new GameObject();
	Sprite* sprite = new Sprite(*GO, "..\\Jogo_Do_Pinguim\\img\\penguinface.png");
	Sound* sound = new Sound(*GO, "..\\Jogo_Do_Pinguim\\audio\\boom.wav");
	Face* face = new Face(*GO);
	GO->box.x = mouseX-(sprite->GetWidth()/2);
	GO->box.y = mouseY-(sprite->GetHeight()/2);
	GO->AddComponent(sprite);
	GO->AddComponent(sound);
	GO->AddComponent(face);
	objectArray.emplace_back(GO);
}

void State::LoadAssets() {
	// pre carrega os assets do state do jogo
}

void State::Update(float dt) {
	State::Input();
	for (auto it = objectArray.begin(); it != objectArray.end(); ++it) {
		(*it)->Update(dt);
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