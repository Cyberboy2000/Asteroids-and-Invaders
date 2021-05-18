#pragma once

namespace sim {
	struct Collision
	{
		/// <summary>
		/// True if a collision has occured.
		/// </summary>
		bool isCollision = false;
		/// <summary>
		/// True if this collision uses physics.
		/// </summary>
		bool isPhysicsCollision = false;
		/// <summary>
		/// True if energy was transferred in the collision.
		/// </summary>
		bool isKinetic = false;
		/// <summary>
		/// The amount to change the horizontal speed of this object by.
		/// </summary>
		float horizontalSpeed = 0;
		/// <summary>
		/// The amount to change the vertical speed of this object by.
		/// </summary>
		float verticalSpeed = 0;
		/// <summary>
		/// The amount to change the horizontal speed of the other object by.
		/// </summary>
		float otherHorizontalSpeed = 0;
		/// <summary>
		/// The amount to change the vertical speed of the other object by.
		/// </summary>
		float otherVerticalSpeed = 0;
		/// <summary>
		/// The amount to displace this object horizontally by.
		/// </summary>
		float horizontalDisplacement = 0;
		/// <summary>
		/// The amount to displace this object vertically by.
		/// </summary>
		float verticalDisplacement = 0;
		/// <summary>
		/// The amount to displace the other object horizontally by.
		/// </summary>
		float otherHorizontalDisplacement = 0;
		/// <summary>
		/// The amount to displace the other object vertically by.
		/// </summary>
		float otherVerticalDisplacement = 0;
		/// Spin angular momentum to add to this object. Not to be confused with total angular momentum, which is conserved, while spin might not be.
		/// </summary>
		float spin = 0;
		/// <summary>
		/// Spin angular momentum to add to the other object. Not to be confused with total angular momentum, which is conserved, while spin might not be.
		/// </summary>
		float otherSpin = 0;
		Collision operator-() const;
		Collision(bool isCollision = false, bool isPhysicsCollision = false, bool isKinetic = false, float horizontalSpeed = 0, float verticalSpeed = 0, float otherHorizontalSpeed = 0, float otherVerticalSpeed = 0, float horizontalDisplacement = 0, float verticalDisplacement = 0, float otherHorizontalDisplacement = 0, float otherVerticalDisplacement = 0, float spin = 0, float otherSpin = 0);
	};
}
