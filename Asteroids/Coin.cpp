#include "Coin.h"
#include "Game.h"
#include "PlayerObject.h"
#include "Util.h"

using namespace sim;

Coin::Coin(int id, Game* sim) : sim::GameObject::GameObject(id, sim) {
	textureFile = "Sprites/Coin.png";
	hasPhysics = false;
	maxSpeed = 500;
	_collider = new Collider(this, 32, 1, 1000, 0.2f);
	boundingRadius = 64;
}

void Coin::tick(float deltaTime) {
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

void Coin::onCollision(Collision collision, GameObject* other) {
	if (other->isPlayer()) {
		GetSim()->GetPlayer()->score++;
		GetSim()->despawnUnit(GetID());
	}
}