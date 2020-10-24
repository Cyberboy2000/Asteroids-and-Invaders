#pragma once
#include "GameObject.h"
#include "DualLaser.h"
#include "Game.h"

namespace sim {
	class Game;
	class GameObject;

	/// <summary>
	/// PC player controlled game object.
	/// </summary>
	class PlayerObject :
		public GameObject
	{
	public:
		void tick(float deltaTime) override;
		void onCollision(Collision collision, GameObject* other) override;
		void Damage(float amount) override;
		void Kill() override;
		bool isPlayer() override;
		float hitStun = 0;
		float maxHitStun = 1;
		float iTime = 0;
		float maxITime = 3;
		float blinkRate = 5;
		int score = 0;
		PlayerObject(int id, Game* sim);
		Weapon* weapon;
		//NonCopyable
		PlayerObject(const PlayerObject&) = delete;
		//NonCopyable
		void operator=(const PlayerObject&) = delete;
	};
}