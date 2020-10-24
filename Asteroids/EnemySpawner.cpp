#include "GameObject.h"
#include "Game.h"
#include "EnemySpawner.h"
#include "PlayerObject.h"
#include "Input.h"
#include "Util.h"
#include "RigType.h"
#include <cmath>

using namespace sim;

void EnemySpawner::tick(float deltaTime) {
	money += deltaTime * difficulty;
	difficulty += deltaTime * difficultyScaling;

	for (int i = 0; i < _waves.size();) {
		EnemyWave* wave = _waves[i];
		if (wave->tick(this, deltaTime)) {
			_waves.erase(_waves.begin() + i);
			delete wave;
		} else {
			i++;
		}
	}

	if (money >= _nextCost) {
		_waves.push_back(_nextEntry->SpawnWave(this));
		NextEntry();
		money -= _nextEntry->GetCost(this);
	}
}

EnemySpawner::EnemySpawner(Game* sim, std::vector<EnemyLibrary::Entry*>* library, float _difficulty, float _scaling, float startingMoney) : _sim(sim), difficulty(_difficulty), difficultyScaling(_scaling), money(startingMoney) {
	_library = library;
	NextEntry();
}

void EnemySpawner::NextEntry() {
	float totalWeight = 0;
	for (EnemyLibrary::Entry* entry : *_library) {
		totalWeight += entry->GetWeight(this);
	}

	if (totalWeight <= 0) {
		throw new std::exception("Total entry weight <= 0");
	}

	float choiceAt = GetSim()->RandFloat(0, totalWeight);
	EnemyLibrary::Entry* choice = nullptr;

	for (EnemyLibrary::Entry* entry : *_library) {
		choiceAt -= entry->GetWeight(this);
		if (choiceAt < 0) {
			choice = entry;
			break;
		}
	}

	if (choice == nullptr) {
		throw new std::exception("Failed to get next entry");
	}

	_nextEntry = choice;
	_nextCost = choice->GetCost(this);
}

Game* EnemySpawner::GetSim() {
	return _sim;
}