#pragma once
#include "GameObject.h"
#include "Game.h"

namespace sim {
	class CorpseObject : public GameObject
	{
	public:
		static CorpseObject* createFromObject(Game* sim, GameObject* parentObj);
		void tick(float deltaTime) override;
		float blinkRate = 5;
		float lifeTime = 2;
		unsigned int particleCount = 100;
		CorpseObject(int id, Game* sim);
		//NonCopyable
		CorpseObject(const CorpseObject&) = delete;
		//NonCopyable
		void operator=(const CorpseObject&) = delete;
	};
}