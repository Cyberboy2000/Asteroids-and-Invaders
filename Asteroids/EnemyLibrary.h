#pragma once
#include <vector>
#include <map>
#include <string>
#include "EnemySpawner.h"
#include "EnemyWave.h"

namespace sim {
	class Game;
	class EnemySpawner;
	class EnemyWave;

	/// <summary>
	/// Lookup of enemy waves for the EnemySpawner to spawn.
	/// </summary>
	namespace EnemyLibrary
	{
		/// <summary>
		/// Alias to index libraries from the main library by.
		/// </summary>
		enum Alias {
			coins,
			asteroids,
			invaders,
		};
		/// <summary>
		/// Abstract library entry, providing an interface for analyzing and spawning waves.
		/// </summary>
		class Entry {
		public:
			/// <summary>
			/// Returns the cost of spawning this wave.
			/// </summary>
			virtual float GetCost(EnemySpawner* spawner) = 0;
			/// <summary>
			/// Returns the weighted chance of spawning this wave.
			/// </summary>
			virtual float GetWeight(EnemySpawner* spawner) = 0;
			/// <summary>
			/// Creates a new wave corresponding to this entry.
			/// </summary>
			virtual EnemyWave* SpawnWave(EnemySpawner* spawner) = 0;
		};

		class Asteroids : public Entry {
		public:
			float GetCost(EnemySpawner* spawner) override;
			float GetWeight(EnemySpawner* spawner) override;
			EnemyWave* SpawnWave(EnemySpawner* spawner) override;
			Asteroids(int count, float minDifficulty);
		private:
			int _count;
			float _minDifficulty;
		};

		class Coins : public Entry {
		public:
			float GetCost(EnemySpawner* spawner) override;
			float GetWeight(EnemySpawner* spawner) override;
			EnemyWave* SpawnWave(EnemySpawner* spawner) override;
		private:
		};

		class Invaders : public Entry {
		public:
			float GetCost(EnemySpawner* spawner) override;
			float GetWeight(EnemySpawner* spawner) override;
			EnemyWave* SpawnWave(EnemySpawner* spawner) override;
		private:
		};

		/// <summary>
		/// Main enemy library. Contains a number of sublibraries (entry vectors) indexed by Aliases.
		/// </summary>
		extern std::map<Alias, std::vector<Entry*>*> libraries;
	};
}