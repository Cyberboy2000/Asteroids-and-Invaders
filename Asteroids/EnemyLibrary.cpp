#include <string>
#include "EnemyLibrary.h"
#include "AsteroidWave.h"
#include "InvaderWave.h"
#include "CoinWave.h"
#include <vector>

using namespace sim;

typedef EnemyLibrary::Asteroids Aster;
typedef EnemyLibrary::Coins C;
typedef EnemyLibrary::Invaders Inv;

//AsteroidWave
float Aster::GetCost(EnemySpawner* spawner) {
	return static_cast<float>(_count);
}
float Aster::GetWeight(EnemySpawner* spawner) {
	if (spawner->difficulty < _minDifficulty) {
		return 0;
	} else {
		return 1;
	}
}
Aster::Asteroids(int count, float minDifficulty) : _count(count), _minDifficulty(minDifficulty) {}

EnemyWave* Aster::SpawnWave(EnemySpawner* spawner) {
	return new AsteroidWave(spawner, _count);
}

//CoinWave
float C::GetCost(EnemySpawner* spawner) {
	return 5;
}
float C::GetWeight(EnemySpawner* spawner) {
	return 1;
}
EnemyWave* C::SpawnWave(EnemySpawner* spawner) {
	return new CoinWave(spawner);
}

//InvaderWave
float Inv::GetCost(EnemySpawner* spawner) {
	return 5;
}
float Inv::GetWeight(EnemySpawner* spawner) {
	return 1;
}
EnemyWave* Inv::SpawnWave(EnemySpawner* spawner) {
	return new InvaderWave(spawner);
}

//Library

std::map<EnemyLibrary::Alias, std::vector<EnemyLibrary::Entry*>*> EnemyLibrary::libraries = std::map<EnemyLibrary::Alias, std::vector<EnemyLibrary::Entry*>*> {
	{EnemyLibrary::Alias::asteroids, new std::vector<EnemyLibrary::Entry*> {
		new Aster(1, 0),
		new Aster(2, 0),
		new Aster(3, 1.01f),
		new Aster(5, 1.5f),
		}
	},
	{EnemyLibrary::Alias::invaders, new std::vector<EnemyLibrary::Entry*> {
		new Inv(),
		}
	},
	{EnemyLibrary::Alias::coins, new std::vector<EnemyLibrary::Entry*> {
		new C(),
		}
	}
};