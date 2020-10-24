#include "StateGame.h"
#include "StatePostGame.h"
#include "StateManager.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "GameParameters.h"
#include "Game.h"
#include "Boardrig.h"
#include "Hud.h"
#include <chrono>
#include <random>

using namespace StateManager;
using namespace sim;

StateGame::StateGame() {
}

void StateGame::SetDifficulty(int i) {
	_difficulty = i;
}

void StateGame::SetGameMode(int i) {
	_gameMode = i;
}

void StateGame::Update(float deltaTime) {
	//Tick game logic
	auto eventQueue = _sim->tick(deltaTime);

	//Check for Game Over
	if (_sim->isFinished()) {
		StateManager::Activate(StatePostGame::state());
	}

	//Send events from the sim to the board
	for (int i = 0; i < eventQueue->size(); i++) {
		_boardrig->onSimEvent(eventQueue->at(i));
	}

	_boardrig->Render();
	_hud->Render();
}
void StateGame::OnUnLoad() {
	delete _sim;
	delete _boardrig;
	delete _hud;
}
void StateGame::OnLoad(sf::RenderWindow* window) {
	//Placeholder random seeds. Uses a combination of random_device (returns hardware randomness when available, but is not reliable on certain platforms) and time
	std::random_device device{};
	uint64_t z = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	uint64_t w = device();

	GameParameters* params;
	if (_gameMode == 0) {
		if (_difficulty == 0) {
			params = &GameParameters::ASTEROIDS_EASY;
		}
		else if (_difficulty == 2) {
			params = &GameParameters::ASTEROIDS_HARD;
		}
		else {
			params = &GameParameters::ASTEROIDS_MEDIUM;
		}
	} else {
		if (_difficulty == 0) {
			params = &GameParameters::INVADERS_EASY;
		}
		else if (_difficulty == 2) {
			params = &GameParameters::INVADERS_HARD;
		}
		else {
			params = &GameParameters::INVADERS_MEDIUM;
		}
	}
	params->seed1 = z;
	params->seed0 = w;
	_sim = new Game{ params };
	_boardrig = new client::Boardrig{ window, _sim };
	_hud = new client::Hud{ window, _sim };
}
void StateGame::restart() {
	sf::RenderWindow* window = _boardrig->window;
	OnUnLoad();
	OnLoad(window);
}