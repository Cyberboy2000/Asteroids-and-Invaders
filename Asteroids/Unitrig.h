#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Boardrig.h"

namespace client {
	class Boardrig;
	/// <summary>
	/// Rig for rendering a simple sprite.
	/// </summary>
	class Unitrig
	{
	public:
		Unitrig(Boardrig* board, sim::GameObject* obj);
		virtual void Render();
		virtual void DebugRender();
		~Unitrig();
		//NonCopyable
		Unitrig(const Unitrig&) = delete;
		//NonCopyable
		void operator=(const Unitrig&) = delete;
	private:
		sim::GameObject* _obj;
		Boardrig* _board;
		sf::Sprite* _sprite;
		sf::CircleShape* _collider;
	};
}

