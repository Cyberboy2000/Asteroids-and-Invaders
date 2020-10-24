#pragma once
#include "GameObject.h"

namespace sim {
	/// <summary>
	/// Basic Asteroid enemy.
	/// </summary>
	class Asteroid :
		public GameObject
	{
	public:
		Asteroid(int id, Game* sim);
		void tick(float deltaTime) override;
	};
}
