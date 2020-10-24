#include "Collision.h"

using namespace sim;

Collision Collision::operator-() const {
	return Collision(isCollision, isPhysicsCollision, isKinetic, otherHorizontalSpeed, otherVerticalSpeed, horizontalSpeed, verticalSpeed, otherHorizontalDisplacement, otherVerticalDisplacement, horizontalDisplacement, verticalDisplacement, otherSpin, spin);
}

Collision::Collision(bool isC, bool isP, bool k, float hSpd, float vSpd, float oHspd, float oVspd, float x, float y, float ox, float oy, float spn, float oSpn) :
	isCollision(isC), isPhysicsCollision(isP), isKinetic(k), horizontalSpeed(hSpd), verticalSpeed(vSpd), otherHorizontalSpeed(oHspd), otherVerticalSpeed(oHspd), horizontalDisplacement(x), verticalDisplacement(y), otherHorizontalDisplacement(ox), otherVerticalDisplacement(oy) , spin(spn), otherSpin(oSpn)
{}