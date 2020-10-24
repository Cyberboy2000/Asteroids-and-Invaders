#define _USE_MATH_DEFINES
#include <cmath>
#include "Invader.h"
#include "InvaderLaser.h"
#include "PlayerObject.h"
#include "CorpseObject.h"
#include "Game.h"
#include "Input.h"
#include "Util.h"

constexpr float TAU = 2 * M_PI;

using namespace sim;

void Invader::tick(float deltaTime) {
	Game* sim = GetSim();
	float h = 0;
	float v = 0;
	float targetAngle = -10;
	float bestTarget = INFINITY;
	

	for (auto pair : GetSim()->gameObjects) {
		GameObject* obj = pair.second;

		if (obj->isPlayer()) {
			float dx = obj->x - x - hAxis * maxSpeed;
			float dy = obj->y - y - hAxis * maxSpeed;
			float dist = sqrtf(dx * dx + dy * dy);
			//float factor = 0.004f * dist - 2;
			float factor = 0.001f * dist - 0.01f;

			h += dx * factor;
			v += dy * factor;

			if (bestTarget > dist) {
				bestTarget = dist;
				targetAngle = atan2f(dy, dx);
			}
		} else if (obj->hasPhysics || obj->faction == player) {
			float dx = obj->x - x;
			float dy = obj->y - y;
			float dist = sqrtf(dx * dx + dy * dy);
			float factor = fmaxf(1 - 0.002f * dist, 0);

			h -= dx * factor;
			v -= dy * factor;
		}
	}

	float inputMagnitude = sqrtf(h * h + v * v);
	if (inputMagnitude > 0) {
		h = h / inputMagnitude;
		v = v / inputMagnitude;
	}

	//Interpolate from our current velocity to target velocity
	float dx = h - hAxis;
	float dy = v - vAxis;
	float dist = sqrtf(dx * dx + dy * dy);
	if (dist <= deltaTime * handling) {
		hAxis = h;
		vAxis = v;
	} else {
		float lerp = deltaTime * handling / dist;
		hAxis += dx * lerp;
		vAxis += dy * lerp;
	}

	//Apply velocity
	x += hAxis * maxSpeed * deltaTime;
	y += vAxis * maxSpeed * deltaTime;

	//Rotate sprite


	/*if (targetAngle != -10) {
		float turnDelta = Util::turnDelta(angle, targetAngle, deltaTime * turnSpeed);
		if (turnDelta != 0) {
			angularVelocity = (turnDelta > 0) ? turnSpeed : -turnSpeed;
			angle = Util::normalizeAngle(angle + turnDelta);
		} else {
			angularVelocity = 0;
		}

		angle += angularVelocity * deltaTime;
	}*/

	if (hAxis != 0 || vAxis != 0) {
		if (angularVelocity > turnSpeed) {
			angularVelocity -= turnSpeed * deltaTime;
		} else if(angularVelocity < -turnSpeed) {
			angularVelocity += turnSpeed * deltaTime;
		} else {
			float targetAngle = atan2f(vAxis, hAxis);
			float turnDelta = Util::turnDelta(angle, targetAngle, deltaTime * turnSpeed);
			angularVelocity = turnDelta / deltaTime;
		}
	} else {
		angularVelocity = 0;
	}

	angle = Util::normalizeAngle(angle + angularVelocity * deltaTime);

	weapon->tick(deltaTime);

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
	if (x < 0.5f * sim->boardW && y < 0.5f * sim->boardH && -x < 0.5f * sim->boardW && -y < 0.5f * sim->boardH
		&& targetAngle != -10 && abs(Util::angleDifference(targetAngle, angle)) < 0.5f) {

		weapon->Fire();
	}
}

Invader::Invader(int i, Game* sim) : GameObject::GameObject(i, sim) {
	textureFile = "Sprites/Invader.png";
	corpseLifeTime = 1;
	boundingRadius = 256;
	maxSpeed = 500 * sim->GetParams()->asteroidSpeed;
	handling = 0.75f * sim->GetParams()->asteroidSpeed;
	turnSpeed = 2;
	hp = 2;
	maxHp = 2;
	faction = invader;
	weapon = new InvaderLaser(this);
	_collider = new Collider(this, 44, 1, 774, 0.1f);
}

void Invader::onCollision(Collision collision, GameObject* other) {
	GameObject::onCollision(collision, other);

	if (collision.isKinetic) {
		Damage(1);
	}
}

void Invader::Kill() {
	GameObject::Kill();
	PlayerObject* player = GetSim()->GetPlayer();
	if (player != nullptr && player->isValid()) {
		player->score++;
	}
}