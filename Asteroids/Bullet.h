#pragma once
#include "GameObject.h"

namespace sim {
	class Bullet :
		public GameObject
	{
	public:
		Bullet(int id, Game* sim);
		void tick(float deltaTime) override;
		void onCollision(Collision collision, GameObject* other) override;
		float damage;
	};
}
