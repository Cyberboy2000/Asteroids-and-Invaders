#pragma once
namespace Util
{
	/// <summary>
	/// Turns between two angles in the range (-2*pi to 4*pi) by a given amount in radians, and returns the new angle.
	/// </summary>
	float turn(float from, float to, float amount);
	/// <summary>
	/// Turns between two angles in the range (-2*pi to 4*pi) by a given amount in radians, and returns the delta between the old angle and the new angle in the range (-pi to pi).
	/// </summary>
	float turnDelta(float from, float to, float amount);
	/// <summary>
	/// Returns the difference in the range (-pi to pi) between the two angles in the range (-2*pi to 4*pi).
	/// </summary>
	float angleDifference(float from, float to);
	/// <summary>
	/// Normalizes an angle in the range (-2*pi to 4*pi) to the range (0 to 2*pi).
	/// </summary>
	float normalizeAngle(float angle);
};

