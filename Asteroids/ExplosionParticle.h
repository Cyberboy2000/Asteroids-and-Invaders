#pragma once
#include "GameObject.h"

namespace sim {
	class ExplosionParticle : public GameObject
	{
	public:
		void tick(float deltaTime) override;
		float lifeTime = 2;
		float maxLifeTime = 2;
		float minLifeTime = 1;
		float minSpeed = 20;
		ExplosionParticle(int id, Game* sim);
		//NonCopyable
		ExplosionParticle(const ExplosionParticle&) = delete;
		//NonCopyable
		void operator=(const ExplosionParticle&) = delete;
	};
}