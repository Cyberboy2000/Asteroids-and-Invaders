#include "InvaderWave.h"
#include "PlayerObject.h"
#include "EnemySpawner.h"
#include "Invader.h"
#include "Input.h"
#include "Game.h"
#include <cmath>

using namespace sim;

InvaderWave::InvaderWave(EnemySpawner* spawner) : EnemyWave(spawner) {}

bool InvaderWave::tick(EnemySpawner* spawner, float deltaTime) {
	Invader* invader = spawner->GetSim()->spawnUnit<Invader>();

	Game* sim = spawner->GetSim();
	PlayerObject* player = sim->GetPlayer();
	int w = sim->boardW;
	int h = sim->boardH;
	//Half of the board circumference
	int b = w + h;
	//Position along the circumference to place the invader at
	int i = sim->RandInt(0, 2 * b);
	float sign = 0.5f;
	if (i >= b) {
		i -= b;
		sign = -0.5f;
	}

	if (i < w) {
		invader->x = i + 0.5f - w * 0.5f;
		invader->y = (2 * invader->boundingRadius + h) * sign;
	} else {
		invader->y = i - w + 0.5f - h * 0.5f;
		invader->x = (2 * invader->boundingRadius + w) * sign;
	}

	if (player != nullptr) {
		float dx = player->x - invader->x;
		float dy = player->y - invader->y;
		float targetAngle = atan2f(dy, dx);
		invader->angle = targetAngle;
	}

	return true;
}