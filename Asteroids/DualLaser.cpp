#include "DualLaser.h"
#include "Bullet.h"
#include <math.h>

using namespace sim;

void DualLaser::Fire() {
	if (CanFire()) {
		Weapon::Fire();
		GameObject* owner = GetOwner();
		Bullet* bullet = owner->GetSim()->spawnUnit<Bullet>();
		bullet->faction = owner->faction;
		bullet->angle = owner->angle;
		bullet->hAxis = cosf(bullet->angle);
		bullet->vAxis = sinf(bullet->angle);
		bullet->maxSpeed = projectileSpeed;
		bullet->x = owner->x + bullet->hAxis * offsetForward - bullet->vAxis * offsetRight * parity;
		bullet->y = owner->y + bullet->vAxis * offsetForward + bullet->hAxis * offsetRight * parity;
		bullet->textureFile = projectileFile;
		bullet->damage = damage;
		parity = -parity;
	}
}

DualLaser::DualLaser(GameObject* owner) : Weapon(owner) {
	cooldownMax = 0.125f;
	cooldown = 0.5f;
	projectileSpeed = 2500;
}