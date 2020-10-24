#pragma once
#include "EnemyWave.h"
#include "EnemySpawner.h"

namespace sim {
	class CoinWave :
		public EnemyWave
	{
	public:
		bool tick(EnemySpawner* spawner, float deltaTime) override;
		CoinWave(EnemySpawner* spawner);
	};
}