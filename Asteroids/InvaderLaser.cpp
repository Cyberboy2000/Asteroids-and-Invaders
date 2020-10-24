#include "InvaderLaser.h"
#include "Bullet.h"
#include <math.h>

using namespace sim;

void InvaderLaser::Fire() {
	if (CanFire()) {
		Weapon::Fire();
		GameObject* owner = GetOwner();
		Bullet* bullet = owner->GetSim()->spawnUnit<Bullet>();
		bullet->faction = owner->faction;
		bullet->angle = owner->angle;
		bullet->hAxis = cosf(bullet->angle);
		bullet->vAxis = sinf(bullet->angle);
		bullet->maxSpeed = projectileSpeed;
		bullet->x = owner->x + bullet->hAxis * offsetForward - bullet->vAxis * offsetRight;
		bullet->y = owner->y + bullet->vAxis * offsetForward + bullet->hAxis * offsetRight;
		bullet->textureFile = projectileFile;
		bullet->damage = damage;
	}
}

InvaderLaser::InvaderLaser(GameObject* owner) : Weapon(owner) {
	cooldownMax = 1 / owner->GetSim()->GetParams()->asteroidSpeed;
	cooldown = cooldownMax;
	projectileSpeed = 1000 * owner->GetSim()->GetParams()->asteroidSpeed;
}