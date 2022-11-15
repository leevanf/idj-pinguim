#include "State.h"

State::State() :
	bg{ "..\\Jogo_Do_Pinguim\\img\\ocean.jpg" },
	music{ "..\\Jogo_Do_Pinguim\\audio\\stageState.ogg" } {
	quitRequested = false;
	music.Play();
}

void State::LoadAssets() {
	// pre carrega os assets do state do jogo
}

void State::Update(float dt) {
	if (SDL_QuitRequested()) {
		quitRequested = true;
	}
}

void State::Render() {
	bg.Render(0, 0);
}