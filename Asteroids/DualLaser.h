#pragma once
#include "Weapon.h"
#include "GameObject.h"
#include <string>

namespace sim {
	class DualLaser :
		public Weapon
	{
	public:
		void Fire() override;
		std::string projectileFile = "Sprites/Bullet.png";
		float offsetRight = 32;
		float offsetForward = 20;
		DualLaser(GameObject* owner);
	private:
		int parity = 1;
	};
}