#include "Weapon.h"

using namespace sim;

void Weapon::tick(float deltaTime) {
	cooldown -= deltaTime;
	if (cooldown < 0) {
		cooldown = 0;
	}
}

void Weapon::Fire() {
	cooldown = cooldownMax;
}

bool Weapon::CanFire() {
	if (cooldown > 0) {
		return false;
	}

	return true;
}

GameObject* Weapon::GetOwner() {
	return _owner;
}
Weapon::Weapon(GameObject* owner) : _owner(owner) {

}