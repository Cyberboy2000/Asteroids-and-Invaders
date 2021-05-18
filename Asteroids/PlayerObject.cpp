#define _USE_MATH_DEFINES
#include "PlayerObject.h"
#include "CorpseObject.h"
#include "Game.h"
#include "Input.h"
#include "Util.h"
#include <cmath>

constexpr float TAU = 2 * M_PI;

using namespace sim;

void PlayerObject::tick(float deltaTime) {
	Game* sim = GetSim();
	float h = Input::HorizontalAxis();
	float v = Input::VerticalAxis();
	float inputMagnitude = Input::AxesMagnitude(h, v);

	//Normalize input if it's greater than 1 in magnitude
	if (inputMagnitude > 1) {
		h = h / inputMagnitude;
		v = v / inputMagnitude;
		inputMagnitude = 1;
	}

	//Interpolate from our current velocity to target velocity
	float dx = h - hAxis;
	float dy = v - vAxis;
	float dist = Input::AxesMagnitude(dx, dy);
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

	//Clamp to within the play area
	float bW = sim->boardW * 0.5f;
	float hW = sim->boardH * 0.5f;
	if (x > bW) {
		x = bW;
	} else if (x < -bW) {
		x = -bW;
	}

	if (y > hW) {
		y = hW;
	} else if (y < -hW) {
		y = -hW;
	}

	if (iTime > 0) {
		iTime -= deltaTime;
		color = sf::Color::White;
		if (iTime <= 0) {
			iTime = 0;
		} else {
			float blink = iTime * blinkRate;
			blink = blink - floorf(blink);
			if (blink >= 0.5f) {
				color = sf::Color(255,128,128);
			}
		}
	}

	weapon->tick(deltaTime);
	if (Input::AttackButtonDown()) {
		weapon->Fire();
	}

	//Rotate sprite
	if (hitStun > 0) {
		angle += angularVelocity * deltaTime;
		hitStun -= deltaTime;
	} else if (h != 0 || v != 0) {
		float targetAngle = atan2f(v, h);
		float turnDelta = Util::turnDelta(angle, targetAngle, deltaTime * turnSpeed);
		angularVelocity = turnDelta / deltaTime;
		angle = Util::normalizeAngle(angle + turnDelta);
	} else {
		angularVelocity = 0;
	}
}

PlayerObject::PlayerObject(int i, Game* sim) : GameObject::GameObject(i, sim) {
	textureFile = "Sprites/Ship.png";
	corpseLifeTime = 2;
	faction = player;
	weapon = new DualLaser(this);
	_collider = new Collider(this, 54, 1, 1160, 0.1f);
}

void PlayerObject::onCollision(Collision collision, GameObject* other) {
	GameObject::onCollision(collision, other);

	if (collision.isKinetic) {
		Damage(1);
		hitStun = maxHitStun;
	}
}

bool PlayerObject::isPlayer() {
	return true;
}
void PlayerObject::Damage(float amount) {
	if (iTime <= 0) {
		GameObject::Damage(amount);
		iTime = maxITime;
	}
}
void PlayerObject::Kill() {
	GameObject::Kill();
	GetSim()->PlayerDestroyed();
}

PlayerObject::~PlayerObject() {
	delete _collider;
	delete weapon;
}