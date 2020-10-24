#pragma once
#include "GameObject.h"
#include "Collision.h"

namespace sim {
	class GameObject;

	/// <summary>
	/// Physics collider.
	/// </summary>
	class Collider
	{
	public:
		Collider(GameObject* parent, float radius, float mass, float momentOfInertia, float friction);
		/// <summary>
		/// Calculates collision with other collider.
		/// </summary>
		Collision CollideWith(Collider* otherCollider);
		/// <summary>
		/// Radius of circle collider.
		/// </summary>
		float mainRadius;
		/// <summary>
		/// Mass of the collider.
		/// </summary>
		float mass;
		/// <summary>
		/// How much the collider resists changes in angular velocity (for a solid sphere, this equals 0.4 * mass * radius^2).
		/// </summary>
		float momentOfInertia;
		float friction;
		Collision currentCollision;
	private:
		GameObject* _parent;
	};
}