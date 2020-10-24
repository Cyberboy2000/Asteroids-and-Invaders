#pragma once
#include "GameParameters.h"
#include "Game.h"
#include "EnemyLibrary.h"
#include "EnemyWave.h"
#include <vector>

namespace sim {
	class EnemyWave;
	class Game;

	namespace EnemyLibrary {
		class Entry;
	}

	/// <summary>
	/// GameObject for spawning waves of enemies.
	/// </summary>
	class EnemySpawner
	{
	public:
		/// <summary>
		/// Advances game logic for all enemy waves and spawning by the given amount in seconds.
		/// </summary>
		void tick(float deltaTime);
		EnemySpawner(Game* sim, std::vector<EnemyLibrary::Entry*>* library, float difficulty, float difficultyScaling, float startingMoney);
		/// <summary>
		/// The rate at which new waves are spawned.
		/// </summary>
		float difficulty = 1;
		/// <summary>
		/// The rate at which the difficulty increases.
		/// </summary>
		float difficultyScaling = 0.01f;
		/// <summary>
		/// Convenience function for accessing the sim.
		/// </summary>
		Game* GetSim();
		/// <summary>
		/// Score that determines when the next wave is spawned.
		/// </summary>
		float money = 0;
		//NonCopyable
		EnemySpawner(const EnemySpawner&) = delete;
		//NonCopyable
		void operator=(const EnemySpawner&) = delete;
	private:
		float _nextCost = 0;
		std::vector<EnemyLibrary::Entry*>* _library;
		EnemyLibrary::Entry* _nextEntry;
		Game* _sim;
		void NextEntry();
		std::vector<EnemyWave*> _waves;
	};
}