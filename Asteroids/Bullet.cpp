#include "Bullet.h"

using namespace sim;

Bullet::Bullet(int id, Game* sim) : sim::GameObject::GameObject(id, sim) {
	textureFile = "Sprites/Bullet.png";
	hasPhysics = false;
	_collider = new Collider(this, 6, 0.01f, 0.32f, 0);
	boundingRadius = 32;
}

void Bullet::tick(float deltaTime) {
	Game* sim = GetSim();
	x += hAxis * maxSpeed * deltaTime;
	y += vAxis * maxSpeed * deltaTime;

	if (x - boundingRadius > 0.5f * sim->boardW && hAxis > 0) {
		sim->despawnUnit(GetID());
	}
	else if (x + boundingRadius < -0.5f * sim->boardW && hAxis < 0) {
		sim->despawnUnit(GetID());
	}
	else if (y - boundingRadius > 0.5f * sim->boardH && vAxis > 0) {
		sim->despawnUnit(GetID());
	}
	else if (y + boundingRadius < -0.5f * sim->boardH && vAxis < 0) {
		sim->despawnUnit(GetID());
	}
}

void Bullet::onCollision(Collision collision, GameObject* other) {
	if (other->faction != faction && other->faction != neutral && other->hasPhysics) {
		other->Damage(damage);
		GetSim()->despawnUnit(GetID());
	}
}