#pragma once
#include "Weapon.h"

namespace sim {
	class InvaderLaser :
		public Weapon
	{
	public:
		void Fire() override;
		std::string projectileFile = "Sprites/BulletPurple.png";
		float offsetRight = 0;
		float offsetForward = 20;
		InvaderLaser(GameObject* owner);
	};
}