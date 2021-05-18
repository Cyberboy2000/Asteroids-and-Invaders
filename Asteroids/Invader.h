#pragma once
#include "GameObject.h"
#include "Weapon.h"
#include <vector>

namespace sim {
	class Invader :
		public GameObject
	{
	public:
		void tick(float deltaTime) override;
		void onCollision(Collision collision, GameObject* other) override;
		void Kill() override;
		Invader(int id, Game* sim);
		Weapon* weapon;
		std::vector<float>* aiForces;
		//NonCopyable
		Invader(const Invader&) = delete;
		//NonCopyable
		void operator=(const Invader&) = delete;
		~Invader();
	};
}