#pragma once
#include <cstdint>
#include <string>
#include "Strings.h"
#include "EnemyLibrary.h"

namespace sim {
	namespace EnemyLibrary {
		class Entry;
		enum Alias;
	}

	struct GameParameters
	{
		uint64_t seed0 = 0;
		uint64_t seed1 = 1;
		int randWarmup = 2;
		float difficulty = 1;
		float difficultyScaling = 0.01f;
		float startingEnemies = 1.5f;
		float coinSpawnRate = 1;
		float coinSpawnRateScaling = 0;
		float startingCoins = 0;
		float asteroidSpeed = 1;
		float iTime = 3;
		EnemyLibrary::Alias enemyList;
		int difficultyIndex;

		static GameParameters ASTEROIDS_EASY;
		static GameParameters ASTEROIDS_MEDIUM;
		static GameParameters ASTEROIDS_HARD;
		static GameParameters INVADERS_EASY;
		static GameParameters INVADERS_MEDIUM;
		static GameParameters INVADERS_HARD;
	};
}
