#include "Collider.h"

using namespace sim;

Collider::Collider(GameObject* parent, float radius, float m, float momentInertia, float f) : _parent(parent), mainRadius(radius), mass(m), momentOfInertia(momentInertia), friction(f) {

}

Collision Collider::CollideWith(Collider* otherCollider) {
	float x = _parent->x;
	float x2 = otherCollider->_parent->x;
	float y = _parent->y;
	float y2 = otherCollider->_parent->y;
	float dx = x2 - x;
	float dy = y2 - y;
	float r = mainRadius + otherCollider->mainRadius;
	float distSqr = (dx * dx + dy * dy);
	Collision collision{};
	if (distSqr < r * r) {
		collision.isCollision = true;

		if (_parent->hasPhysics && otherCollider->_parent->hasPhysics) {
			collision.isPhysicsCollision = true;

			float speed = _parent->maxSpeed;
			float hSpeed = speed * _parent->hAxis;
			float vSpeed = speed * _parent->vAxis;
			float speed2 = otherCollider->_parent->maxSpeed;
			float hSpeed2 = speed2 * otherCollider->_parent->hAxis;
			float vSpeed2 = speed2 * otherCollider->_parent->vAxis;
			float dHspeed = hSpeed2 - hSpeed;
			float dVspeed = vSpeed2 - vSpeed;
			//The change in velocity is proportional to the dot product of the deltaPosition and the deltaVelocity (divided by the distance).
			//In other words, a head on collision has a larger effect than grazing.
			float dot = dHspeed * dx + dVspeed * dy;
			//
			float massFactor = 2 / (mass + otherCollider->mass);
			float mass1 = mass * massFactor;
			float mass2 = otherCollider->mass * massFactor;
			//
			float displacement = r / sqrtf(distSqr) - 1;
			float displacement1 = -mass2 * displacement;
			float displacement2 = mass1 * displacement;
			collision.horizontalDisplacement = displacement1 * dx;
			collision.verticalDisplacement = displacement1 * dy;
			collision.otherHorizontalDisplacement = displacement2 * dx;
			collision.otherVerticalDisplacement = displacement2 * dy;
			//If the dot product is positive, that means the objects are already moving away from each other.
			if (dot < 0) {
				collision.isKinetic = true;
				//The angle of change is opposite to the angle of collision (deltaPosition).
				//Conveniently, dividing by the distance squared normalizes both the dot product and the deltaPosition.
				float change = dot / distSqr;

				collision.horizontalSpeed = mass2 * dx * change;
				collision.verticalSpeed = mass2 * dy * change;
				collision.otherHorizontalSpeed = -mass1 * dx * change;
				collision.otherVerticalSpeed = -mass1 * dy * change;

				//Now, the transfer of angular momentum isn't well defined since it depends on friction and other factors, and the code above is for elastic collisions only meaning no friction.
				//Also I can't be bothered with orbital angular momentum and stuff. See the following as a pure game design choice rather than any attempt at accurate physics simulation.
				//Approximate the change in angular velocity as proportional to the cross product, meaning hitting the object at an angle causes more spin than head on.
				float cross = dVspeed * dx - dHspeed * dy;
				collision.spin = friction * otherCollider->friction * otherCollider->mass * cross;
				collision.otherSpin = -friction * otherCollider->friction * mass * cross;

				/*float invInert = 1 / momentOfInertia;
				float otherInvInert = 1 / otherCollider->momentOfInertia;

				//Real duct-tape solution here. We calculate the rotational energy added.
				float energy = collision.spin * (0.5f * collision.spin * invInert + _parent->angularVelocity) + collision.otherSpin * (0.5f * collision.otherSpin * otherInvInert + otherCollider->_parent->angularVelocity);
				float kinetic = 0.5f * dHspeed * dHspeed + dVspeed + dVspeed;
				//And then subtract it from the kinetic energy.
				float newKinetic = kinetic - energy;
				float cx = 0.5f * (hSpeed + hSpeed2);
				float cy = 0.5f * (vSpeed + vSpeed2);*/

				/*float orbital = mass * sqrt((x*x + y*y) * (hSpeed * hSpeed + vSpeed * vSpeed));
				float orbital2 = mass * sqrt((x2*x2 + y2*y2) * (hSpeed2 * hSpeed2 + vSpeed * vSpeed2));
				float hSpeed3 = hSpeed + collision.hSpeedChange;
				float vSpeed3 = vSpeed + collision.vSpeedChange;
				float hSpeed4 = hSpeed2 - collision.hSpeedChange;
				float vSpeed4 = vSpeed2 - collision.vSpeedChange;
				float orbital3 = mass * sqrt((x*x + y*y) * (hSpeed3 * hSpeed3 + vSpeed3 * vSpeed3));
				float orbital4 = mass * sqrt((x2*x2 + y2*y2) * (hSpeed4 * hSpeed4 + vSpee4 * vSpeed4));

				float angularMomentumChange = orbital + orbital2 - orbital3 - orbital4;
				print(angularMomentumChange);*/
			}
		}
	}

	return collision;
}