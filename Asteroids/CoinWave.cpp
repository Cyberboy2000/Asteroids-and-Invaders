#include "CoinWave.h"
#include "PlayerObject.h"
#include "EnemySpawner.h"
#include "Coin.h"
#include "Input.h"
#include "Game.h"
#include <cmath>

using namespace sim;

CoinWave::CoinWave(EnemySpawner* spawner) : EnemyWave(spawner) {}

bool CoinWave::tick(EnemySpawner* spawner, float deltaTime) {
	Coin* coin = spawner->GetSim()->spawnUnit<Coin>();

	Game* sim = spawner->GetSim();
	PlayerObject* player = sim->GetPlayer();
	int w = sim->boardW;
	int h = sim->boardH;
	//Half of the board circumference
	int b = w + h;
	//Position along the circumference to place the coin at
	int i = sim->RandInt(0, 2 * b);
	float sign = 0.5f;
	if (i >= b) {
		i -= b;
		sign = -0.5f;
	}

	if (i < w) {
		coin->x = i + 0.5f - w * 0.5f;
		coin->y = (2 * coin->boundingRadius + h) * sign;

		//Randomize target angle
		float dx = coin->x + w * sim->RandFloat(-0.25f, 0.25);
		float dist = -Input::AxesMagnitude(dx, coin->y);

		coin->hAxis = dx / dist;
		coin->vAxis = coin->y / dist;
	} else {
		coin->y = i - w + 0.5f - h * 0.5f;
		coin->x = (2 * coin->boundingRadius + w) * sign;

		//Randomize target angle
		float dy = coin->y + h * sim->RandFloat(-0.25f, 0.25);
		float dist = -Input::AxesMagnitude(coin->x, dy);

		coin->vAxis = dy / dist;
		coin->hAxis = coin->x / dist;
	}

	return true;
}