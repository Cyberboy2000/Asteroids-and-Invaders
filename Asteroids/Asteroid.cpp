#define _USE_MATH_DEFINES
#include "Asteroid.h"
#include "Game.h"
#include "Util.h"
#include <cmath>

constexpr float TAU = 2 * M_PI;

using namespace sim;

Asteroid::Asteroid(int id, Game* sim) : sim::GameObject::GameObject(id, sim) {
	textureFile = "Sprites/AsteroidL.png";
	faction = asteroid;
	_collider = new Collider(this, 88, 2, 6200, 0.2f);
	boundingRadius = 200;
}

void Asteroid::tick(float deltaTime) {
	Game* sim = GetSim();
	x += hAxis * maxSpeed * deltaTime;
	y += vAxis * maxSpeed * deltaTime;

	angle = Util::normalizeAngle(angle + angularVelocity * deltaTime);

	if (x - boundingRadius > 0.5f * sim->boardW && hAxis > 0) {
		sim->despawnUnit(GetID());
	} else if (x + boundingRadius < -0.5f * sim->boardW && hAxis < 0) {
		sim->despawnUnit(GetID());
	} else if (y - boundingRadius > 0.5f * sim->boardH && vAxis > 0) {
		sim->despawnUnit(GetID());
	} else if (y + boundingRadius < -0.5f * sim->boardH && vAxis < 0) {
		sim->despawnUnit(GetID());
	}
}