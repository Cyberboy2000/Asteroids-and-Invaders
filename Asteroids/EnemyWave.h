#pragma once
#include "EnemySpawner.h"

namespace sim {
	class EnemySpawner;

	/// <summary>
	/// Abstract group of enemies to spawn.
	/// </summary>
	class EnemyWave
	{
	public:
		EnemyWave(EnemySpawner* spawner);
		/// <summary>
		/// Advances wave logic by the given amount in seconds, and returns true when the wave is completed.
		/// </summary>
		virtual bool tick(EnemySpawner* spawner, float deltaTime) = 0;
		//NonCopyable
		EnemyWave(const EnemyWave&) = delete;
		//NonCopyable
		void operator=(const EnemyWave&) = delete;
	protected:
		EnemySpawner* spawner;
	};
}