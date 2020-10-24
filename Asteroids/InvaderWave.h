#pragma once
#include "EnemyWave.h"
#include "EnemySpawner.h"

namespace sim {
	class InvaderWave :
		public EnemyWave
	{
	public:
		InvaderWave(EnemySpawner* spawner);
		bool tick(EnemySpawner* spawner, float deltaTime) override;
	};
}

