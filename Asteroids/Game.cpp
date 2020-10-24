#include "Game.h"
#include "GameObject.h"
#include "PlayerObject.h"
#include "EnemySpawner.h"
#include "Rand.h"
#include "SimEvent.h"
#include "EnemyLibrary.h"

using namespace sim;

Game::Game(GameParameters* parameters) : gameObjects(), _eventQueue(new std::vector<SimEvent>), _params(parameters), _rand(new Rand(parameters->seed0, parameters->seed1)) {
	for (int i = 0; i < parameters->randWarmup; i++) {
		_rand->Next();
	}
	_player = spawnUnit<PlayerObject>();
	_player->maxITime = parameters->iTime;
	_spawner = new EnemySpawner(this, EnemyLibrary::libraries[parameters->enemyList], parameters->difficulty, parameters->difficultyScaling, parameters->startingEnemies);
	_coins = new EnemySpawner(this, EnemyLibrary::libraries[EnemyLibrary::coins], parameters->coinSpawnRate, parameters->coinSpawnRateScaling, parameters->startingCoins);
}

Game::~Game() {
	for (auto obj : gameObjects)
	{
		delete obj.second;
	}
	delete _spawner;
	delete _coins;
	delete _eventQueue;
}

void Game::despawnUnit(int id) {
	if (gameObjects.find(id) != gameObjects.end()) {
		gameObjects[id]->inValidate();
		QueueEvent(SimEvent(SimEvent::unitDestroyed, id));
	}
}

void Game::QueueEvent(SimEvent ev) {
	_eventQueue->push_back(ev);
}

bool Game::isFinished() {
	return _player == nullptr;
}

std::vector<SimEvent>* Game::tick(float deltaTime) {
	if (_isTicking) {
		throw std::exception("Recursive ticking is not allowed.");
	}

	_isTicking = true;
	if (_hasSentStartEvents) {
		_eventQueue->clear();
	}
	std::map<int, GameObject*> temp = std::map<int, GameObject*>(gameObjects);
	for (auto obj : temp)
	{
		Collider* collider = obj.second->GetCollider();
		if (collider != nullptr) {
			collider->currentCollision = Collision();
		}
		if (obj.second->isValid()) {
			obj.second->tick(deltaTime);
		}
	}
	for (auto obj : temp)
	{
		Collider* collider = obj.second->GetCollider();
		if (obj.second->isValid() && collider != nullptr) {
			for (auto obj2 : temp)
			{
				if (obj2.second->isValid() && obj2.second->GetID() > obj.second->GetID()) {
					Collider* collider2 = obj2.second->GetCollider();
					if (collider2 != nullptr) {
						Collision collision = collider->CollideWith(obj2.second->GetCollider());
						if (collision.isCollision) {
							obj.second->onCollision(collision, obj2.second);
							obj2.second->onCollision(-collision, obj.second);
							collider->currentCollision = collision;
							collider2->currentCollision = -collision;
						}
					}
				}
			}
		}
	}

	_spawner->tick(deltaTime);
	_coins->tick(deltaTime);

	for (auto obj : temp) {
		if (!obj.second->isValid()) {
			gameObjects.erase(obj.second->GetID());
			delete obj.second;
		}
	}

	_isTicking = false;
	_hasSentStartEvents = true;

	return _eventQueue;
}

PlayerObject* Game::GetPlayer() {
	return _player;
}

EnemySpawner* Game::GetEnemy() {
	return _spawner;
}

EnemySpawner* Game::GetCoins() {
	return _coins;
}

GameParameters* Game::GetParams() {
	return _params;
}

int Game::RandInt(int a, int b) {
	return _rand->Int(a, b);
}

double Game::RandDouble(double a, double b) {
	return _rand->Double(a, b);
}

float Game::RandFloat(float a, float b) {
	return _rand->Float(a, b);
}

void Game::PlayerDestroyed() {
	_player = nullptr;
	_spawner->difficulty = 0;
	_spawner->difficultyScaling = 0;
	_coins->difficulty = 0;
	_coins->difficultyScaling = 0;
}