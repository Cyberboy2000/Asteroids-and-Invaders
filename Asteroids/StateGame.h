#pragma once
#include "GameParameters.h"
#include "State.h"
#include "Game.h"
#include "Boardrig.h"
#include "Hud.h"

namespace StateManager {
	class StateGame : public State
	{
	public:
		void Update(float deltaTime) override;
		void OnUnLoad() override;
		void OnLoad(sf::RenderWindow* window) override;
		void restart();
		void SetDifficulty(int difficulty);
		void SetGameMode(int gameMode);
		StateGame();
		static StateGame* state()
		{
			static StateGame* instance = new StateGame();
			return instance;
		}
	private:
		int _difficulty;
		int _gameMode;
		sim::Game* _sim;
		client::Boardrig* _boardrig;
		client::Hud* _hud;
	};
}