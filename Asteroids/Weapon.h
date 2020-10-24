#pragma once
#include "GameObject.h"
#include <string>

namespace sim {
	class GameObject;

	class Weapon
	{
		public:
		virtual void tick(float deltaTime);
		virtual void Fire();
		virtual bool CanFire();

		GameObject* GetOwner();
		Weapon(GameObject* owner);

		float cooldown = 0;
		float cooldownMax = 1;
		float damage = 1;
		float projectileSpeed = 1000;

		//NonCopyable
		Weapon(const Weapon&) = delete;
		//NonCopyable
		void operator=(const Weapon&) = delete;
	private:
		GameObject* _owner;
	};
}
