#pragma once
#include "EnemyWave.h"
#include "EnemySpawner.h"

namespace sim {
	class AsteroidWave :
		public EnemyWave
	{
	public:
		AsteroidWave(EnemySpawner* spawner, int count);
		bool tick(EnemySpawner* spawner, float deltaTime) override;
		float minDelay = 0.1f;
		float maxDelay = 0.75f;
		float minSpeedFactor = 0.25f;
	private:
		int _count;
		float _delay;
		float GetDelay(EnemySpawner* spawner);
	};
}