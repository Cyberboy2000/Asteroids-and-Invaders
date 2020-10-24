#define _USE_MATH_DEFINES
#include "PlayerObject.h"
#include "AsteroidWave.h"
#include "EnemySpawner.h"
#include "Asteroid.h"
#include "Input.h"
#include "Game.h"
#include <cmath>

using namespace sim;

AsteroidWave::AsteroidWave(EnemySpawner* spawner, int count) : EnemyWave(spawner) {
	_count = count;
	_delay = GetDelay(spawner);
}

bool AsteroidWave::tick(EnemySpawner* spawner, float deltaTime) {
	_delay -= deltaTime;

	if (_delay <= 0) {
		_delay += GetDelay(spawner);
		_count -= 1;

		Asteroid* asteroid = spawner->GetSim()->spawnUnit<Asteroid>();

		Game* sim = spawner->GetSim();
		PlayerObject* player = sim->GetPlayer();
		int w = sim->boardW;
		int h = sim->boardH;
		//Half of the board circumference
		int b = w + h;
		//Position along the circumference to place the asteroid at
		int i = sim->RandInt(0, 2 * b);
		float sign = 0.5f;
		if (i >= b) {
			i -= b;
			sign = -0.5f;
		}

		float speed = sim->RandFloat(minSpeedFactor, 1) * sim->GetParams()->asteroidSpeed;

		if (i < w) {
			asteroid->x = i + 0.5f - w * 0.5f;
			asteroid->y = (2 * asteroid->boundingRadius + h) * sign;

			//Randomize target angle
			float dx = asteroid->x + w * sim->RandFloat(-0.5f,0.5);
			float dist = -Input::AxesMagnitude(dx,asteroid->y);

			asteroid->hAxis = speed * dx / dist;
			asteroid->vAxis = speed * asteroid->y / dist;
		} else {
			asteroid->y = i - w + 0.5f - h * 0.5f;
			asteroid->x = (2 * asteroid->boundingRadius + w) * sign;

			//Randomize target angle
			float dy = asteroid->y + h * sim->RandFloat(-0.5f, 0.5);
			float dist = -Input::AxesMagnitude(asteroid->x, dy);

			asteroid->vAxis = speed * dy / dist;
			asteroid->hAxis = speed * asteroid->x / dist;
		}

		asteroid->angularVelocity = asteroid->turnSpeed * sim->RandFloat(-1, 1);

		if (_count <= 0) {
			return true;
		}
	}

	return false;
}

float AsteroidWave::GetDelay(EnemySpawner* spawner) {
	return spawner->GetSim()->RandFloat(minDelay, maxDelay);
}