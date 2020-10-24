#include "CorpseObject.h"
#include "ExplosionParticle.h"
#include "Util.h"

using namespace sim;

void CorpseObject::tick(float deltaTime) {
	Game* sim = GetSim();
	x += hAxis * maxSpeed * deltaTime;
	y += vAxis * maxSpeed * deltaTime;

	angle = Util::normalizeAngle(angle + angularVelocity * deltaTime);

	lifeTime -= deltaTime;

	color = sf::Color::White;
	float blink = lifeTime * blinkRate;
	blink = blink - floorf(blink);
	if (blink >= 0.5f) {
		color = sf::Color(255, 128, 128);
	}

	if (lifeTime <= 0) {
		GetSim()->despawnUnit(GetID());
		for (int i = 0; i < particleCount; i++) {
			ExplosionParticle* particle = GetSim()->spawnUnit<ExplosionParticle>();
			particle->x = x;
			particle->y = y;
		}
	}
}

CorpseObject::CorpseObject(int i, Game* sim) : GameObject::GameObject(i, sim) {
}

CorpseObject* CorpseObject::createFromObject(Game* sim, GameObject* parentObj) {
	CorpseObject* corpse = sim->spawnUnit<CorpseObject>();

	corpse->x = parentObj->x;
	corpse->y = parentObj->y;
	corpse->angle = parentObj->angle;
	corpse->textureFile = parentObj->textureFile;
	corpse->rigType = parentObj->rigType;
	corpse->hAxis = parentObj->hAxis;
	corpse->vAxis = parentObj->vAxis;
	corpse->maxSpeed = parentObj->maxSpeed;
	corpse->handling = parentObj->handling;
	corpse->turnSpeed = parentObj->turnSpeed;
	corpse->angularVelocity = parentObj->angularVelocity;
	corpse->boundingRadius = parentObj->boundingRadius;
	corpse->hasPhysics = parentObj->hasPhysics;
	corpse->isVisible = parentObj->isVisible;
	corpse->color = parentObj->color;

	Collider* objCollider = parentObj->GetCollider();
	corpse->_collider = new Collider(corpse, objCollider->mainRadius, objCollider->mass, objCollider->momentOfInertia, objCollider->friction);

	return corpse;
}