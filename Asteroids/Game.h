#pragma once
#include <map>
#include <vector>
#include "GameParameters.h"
#include "GameObject.h"
#include "SimEvent.h"
#include "Rand.h"

namespace sim {
	class GameObject;
	class PlayerObject;
	class EnemySpawner;
	struct GameParameters;

	/// <summary>
	/// Main simulation engine for the game session.
	/// </summary>
	class Game
	{
	public:
		/// <summary>
		/// Returns true when this game session is over.
		/// </summary>
		bool isFinished();
		/// <summary>
		/// Advances game logic by the given amount in seconds and returns events to process.
		/// </summary>
		/// <param name='deltaTime'>Time in seconds since last tick.</param>
		std::vector<SimEvent>* tick(float deltaTime);
		/// <summary>
		/// The width of the playable space.
		/// </summary>
		int boardW = 2400;
		/// <summary>
		/// The height of the playable space.
		/// </summary>
		int boardH = 1800;
		/// <summary>
		/// Constructs a new GameObject of type T and assigns it to the game world.
		/// </summary>
		template<class T> T* spawnUnit() {
			//Fuuuu why are template functions definitions forced to be in the header file? It's dumb.

			//Make sure the spawned object doesn't alter nextId before we assign it
			int id = _nextId;
			_nextId++;

			T* newObj = new T{ id, this };
			gameObjects[id] = newObj;

			QueueEvent(SimEvent(SimEvent::unitCreated, id));
			return newObj;
		}
		/// <summary>
		/// Removes the GameObject with the given id from the game world and frees up its memory.
		/// </summary>
		void despawnUnit(int id);
		///<summary>Generate signed integer between a (inclusive) and b (exclusive).</summary>
		int RandInt(int a, int b);
		///<summary>Generate double precision floating point value between a and b.</summary>
		double RandDouble(double a, double b);
		///<summary>Generate single precision floating point value between a and b.</summary>
		float RandFloat(float a, float b);

		/// <summary>
		/// Sets up game logic by spawning initial game objects.
		/// </summary>
		Game(GameParameters* parameters);
		~Game();

		/// <summary>
		/// Queue event to send to the client.
		/// </summary>
		void QueueEvent(SimEvent ev);

		/// <summary>
		/// Returns the player GameObject.
		/// </summary>
		PlayerObject* GetPlayer();
		/// <summary>
		/// Returns the main EnemySpawner for spawning enemy GameObjects.
		/// </summary>
		EnemySpawner* GetEnemy();
		/// <summary>
		/// Returns the main EnemySpawner for spawning coin GameObjects.
		/// </summary>
		EnemySpawner* GetCoins();
		/// <summary>
		/// All units in the game world, mapped by their id.
		/// </summary>
		std::map<int,GameObject*> gameObjects;
		/// <summary>
		/// Signal to the sim that the player has been destroyed.
		/// </summary>
		void PlayerDestroyed();
		GameParameters* GetParams();

		//NonCopyable
		Game(const Game&) = delete;
		//NonCopyable
		void operator=(const Game&) = delete;
	private:
		int _nextId = 100;
		bool _isTicking = false;
		bool _hasSentStartEvents = false;
		GameParameters* _params;
		PlayerObject* _player;
		EnemySpawner* _spawner;
		EnemySpawner* _coins;
		Rand* _rand;
		/// <summary>
		/// Queue of events to send to the client.
		/// </summary>
		std::vector<SimEvent>* _eventQueue;
	};
}