#include "Game.h"
#include "Resources.h"
#include <cstdlib>
#include <ctime>

Game* Game::instance;
Game::Game(std::string title, int width, int height) {
	srand(time(NULL));
	if (instance != nullptr) {
		throw std::runtime_error("There is already an instance");
	}
	else {
		instance = this;
	}
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
		std::cout << "SDL_Init failed: " << SDL_GetError() << "\n";
		Game::~Game();
	}
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0) {
		std::cout << "IMG_Init failed: " << SDL_GetError() << "\n";
		Game::~Game();
	}
	if (Mix_Init(MIX_INIT_MP3) == 0) {
		std::cout << "Mix_Init failed: " << SDL_GetError() << "\n";
		Game::~Game();
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
		std::cout << "Mix_OpenAudio failed: " << SDL_GetError() << "\n";
		Game::~Game();
	}
	Mix_AllocateChannels(32);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (window == nullptr) {
		std::cout << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
		Game::~Game();
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		std::cout << "SDL_CreateRenderer failed: " << SDL_GetError() << "\n";
		Game::~Game();
	}

	state = new State();
	frameStart = 0;
	dt = 0;
}

Game::~Game() {
	delete state;
	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearSounds();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::Run() {
	state->Start();
	while (state->QuitRequested() == false) {
		Game::CalculateDeltaTime();
		InputManager::GetInstance().Update();
		state->Update(Game::GetDeltaTime());
		state->Render();
		SDL_RenderPresent(renderer);
		SDL_Delay(33);
	}
}

Game& Game::GetInstance() {
	if (Game::instance == nullptr) {
		instance = new Game("Lucas Monteiro Miranda, 170149684", 1024, 600);
	}
	return *instance;
}

void Game::CalculateDeltaTime() {
	Uint32 ticks = SDL_GetTicks();
	dt = (ticks - frameStart) / 1000.0;
	frameStart = ticks;
}