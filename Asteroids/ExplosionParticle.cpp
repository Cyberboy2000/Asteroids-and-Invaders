#define _USE_MATH_DEFINES

#include "ExplosionParticle.h"
#include "Util.h"
#include <cmath>

using namespace sim;

void ExplosionParticle::tick(float deltaTime) {
	Game* sim = GetSim();

	x += hAxis * maxSpeed * deltaTime;
	y += vAxis * maxSpeed * deltaTime;

	angle = Util::normalizeAngle(angle + angularVelocity * deltaTime);

	lifeTime -= deltaTime;

	color = sf::Color(255,255,255,255 * lifeTime / maxLifeTime);

	if (x - boundingRadius > 0.5f * sim->boardW && hAxis > 0) {
		sim->despawnUnit(GetID());
	} else if (x + boundingRadius < -0.5f * sim->boardW && hAxis < 0) {
		sim->despawnUnit(GetID());
	} else if (y - boundingRadius > 0.5f * sim->boardH && vAxis > 0) {
		sim->despawnUnit(GetID());
	} else if (y + boundingRadius < -0.5f * sim->boardH && vAxis < 0) {
		sim->despawnUnit(GetID());
	} else if (lifeTime <= 0) {
		GetSim()->despawnUnit(GetID());
	}
}

ExplosionParticle::ExplosionParticle(int i, Game* sim) : GameObject::GameObject(i, sim) {
	textureFile = "Sprites/ExplosionParticle"+std::to_string(sim->RandInt(1,4))+".png";
	hasPhysics = false;
	lifeTime = sim->RandFloat(minLifeTime, maxLifeTime);
	angle = sim->RandFloat(0, 2 * M_PI);
	angularVelocity = handling * sim->RandFloat(-1, 1);
	float vAngle = sim->RandFloat(0, 2 * M_PI);
	hAxis = cosf(vAngle);
	vAxis = sinf(vAngle);
	maxSpeed = sim->RandFloat(minSpeed, maxSpeed);
}