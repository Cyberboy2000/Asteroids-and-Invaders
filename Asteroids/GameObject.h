#pragma once
#include <string>
#include "RigType.h"
#include "Game.h"
#include "Collision.h"
#include "Collider.h"
#include "Faction.h"
#include "SFML/Graphics/Color.hpp"
namespace sim {
	class Game;
	class Collider;
	class Weapon;

	/// <summary>
	/// Abstract for all units in the game world to inherit from.
	/// </summary>
	class GameObject
	{
	public:
		/// <summary>
		/// Advances game logic for this object by the given amount in seconds.
		/// </summary>
		/// <param name='deltaTime'>Time in seconds since last tick.</param>
		virtual void tick(float deltaTime) = 0;
		/// <summary>
		/// The x position of this object in game world space.
		/// </summary>
		float x = 0;
		/// <summary>
		/// The y position of this object in game world space.
		/// </summary>
		float y = 0;
		/// <summary>
		/// The angle of this object in radians counterclockwise.
		/// </summary>
		float angle = 0;
		/// <summary>
		/// The texture used to render this object.
		/// </summary>
		std::string textureFile = "";
		/// <summary>
		/// Identifier unique to this game object.
		/// </summary>
		int GetID();
		/// <summary>
		/// The type of rig this object should use for rendering.
		/// </summary>
		client::RigType rigType = client::RigType::unitrig;
		/// <summary>
		/// Convenience function for accessing the sim.
		/// </summary>
		Game* GetSim();

		/// <summary>
		/// The horizontal axis of this object's velocity, normalized to between -1 and 1.
		/// </summary>
		float hAxis = 0;
		/// <summary>
		/// The vertical axis of this object's velocity, normalized to between -1 and 1.
		/// </summary>
		float vAxis = 0;
		/// <summary>
		/// The maximum speed of this object.
		/// </summary>
		float maxSpeed = 1000;
		/// <summary>
		/// The rate at which this object can change its velocity.
		/// </summary>
		float handling = 4;
		/// <summary>
		/// The speed at which this object can change its angle.
		/// </summary>
		float turnSpeed = 6;
		/// <summary>
		/// The speed at which this object is currently changing its angle.
		/// </summary>
		float angularVelocity = 0;
		/// <summary>
		/// Approximation of the radius needed to completely encompass the object.
		/// </summary>
		float boundingRadius = 0;
		/// <summary>
		/// Returns the collider this object uses to detect collisions.
		/// </summary>
		Collider* GetCollider();
		/// <summary>
		/// Whether this object uses physics to bounce off other physics objects.
		/// </summary>
		bool hasPhysics = true;
		/// <summary>
		/// Whether this object is being rendered.
		/// </summary>
		bool isVisible = true;
		/// <summary>
		/// The color of the object.
		/// </summary>
		sf::Color color = sf::Color::White;
		/// <summary>
		/// The faction this unit belongs to.
		/// </summary>
		Faction faction = neutral;

		virtual bool isPlayer();
		/// <summary>
		/// Performs the necessary physics in reaction to a collision.
		/// </summary>
		virtual void onCollision(Collision collision, GameObject* object);

		GameObject(int id, Game* sim);
		/// <summary>
		/// Returns false if this object is marked for deletion, returns true if it's ok to use.
		/// </summary>
		bool isValid();
		/// <summary>
		/// Marks this object for deletion.
		/// </summary>
		void inValidate();
		/// <summary>
		/// Deals damage to this object.
		/// </summary>
		virtual void Damage(float amount);
		/// <summary>
		/// Kills and despawns this object.
		/// </summary>
		virtual void Kill();
		float hp = 3;
		float maxHp = 3;
		float corpseLifeTime = 0;
		~GameObject();
		//NonCopyable
		GameObject(const GameObject&) = delete;
		//NonCopyable
		void operator=(const GameObject&) = delete;
	protected:
		Collider* _collider = nullptr;
	private:
		int _id;
		Game* _sim;
		bool _valid = true;
	};
}