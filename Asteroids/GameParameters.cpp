#include <string>
#include "GameParameters.h"
#include "EnemyLibrary.h"
#include "Strings.h"

using namespace sim;

GameParameters GameParameters::ASTEROIDS_EASY{
	.difficulty = 0.8f,
	.difficultyScaling = 0.007f,
	.startingEnemies = 1,
	.coinSpawnRate = 1,
	.coinSpawnRateScaling = 0,
	.startingCoins = 0,
	.asteroidSpeed = 0.8f,
	.iTime = 3,
	.enemyList = EnemyLibrary::Alias::asteroids,
	.difficultyIndex = 0,
};
GameParameters GameParameters::ASTEROIDS_MEDIUM{
	.difficulty = 1,
	.difficultyScaling = 0.01f,
	.startingEnemies = 1.5f,
	.coinSpawnRate = 1,
	.coinSpawnRateScaling = 0,
	.startingCoins = 0,
	.asteroidSpeed = 0.9f,
	.iTime = 2.5f,
	.enemyList = EnemyLibrary::Alias::asteroids,
	.difficultyIndex = 1,
};
GameParameters GameParameters::ASTEROIDS_HARD{
	.difficulty = 1.2f,
	.difficultyScaling = 0.012f,
	.startingEnemies = 2,
	.coinSpawnRate = 1,
	.coinSpawnRateScaling = 0,
	.startingCoins = 0,
	.asteroidSpeed = 1,
	.iTime = 2,
	.enemyList = EnemyLibrary::Alias::asteroids,
	.difficultyIndex = 2,
};
GameParameters GameParameters::INVADERS_EASY{
	.difficulty = 0.8f,
	.difficultyScaling = 0.007f,
	.startingEnemies = 4,
	.coinSpawnRate = 0,
	.coinSpawnRateScaling = 0,
	.startingCoins = 0,
	.asteroidSpeed = 0.8f,
	.iTime = 3,
	.enemyList = EnemyLibrary::Alias::invaders,
	.difficultyIndex = 3,
};
GameParameters GameParameters::INVADERS_MEDIUM{
	.difficulty = 1,
	.difficultyScaling = 0.01f,
	.startingEnemies = 4,
	.coinSpawnRate = 0,
	.coinSpawnRateScaling = 0,
	.startingCoins = 0,
	.asteroidSpeed = 0.9f,
	.iTime = 2.5f,
	.enemyList = EnemyLibrary::Alias::invaders,
	.difficultyIndex = 4,
};
GameParameters GameParameters::INVADERS_HARD{
	.difficulty = 1.2f,
	.difficultyScaling = 0.012f,
	.startingEnemies = 4,
	.coinSpawnRate = 0,
	.coinSpawnRateScaling = 0,
	.startingCoins = 0,
	.asteroidSpeed = 1,
	.iTime = 2,
	.enemyList = EnemyLibrary::Alias::invaders,
	.difficultyIndex = 5,
};