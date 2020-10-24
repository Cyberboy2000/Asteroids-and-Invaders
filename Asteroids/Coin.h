#pragma once
#include "GameObject.h"

namespace sim {
	class Coin :
		public GameObject
	{
	public:
		Coin(int id, Game* sim);
		void tick(float deltaTime) override;
		void onCollision(Collision collision, GameObject* other) override;
	};
}