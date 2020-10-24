#include "GameObject.h"
#include "CorpseObject.h"

using namespace sim;

GameObject::GameObject(int i, Game* sim) : _id(i), _sim(sim) {}
int GameObject::GetID() { return _id; }
Game* GameObject::GetSim() { return _sim; }
Collider* GameObject::GetCollider() { return _collider; };
void GameObject::onCollision(Collision collision, GameObject* object) {
	x += collision.horizontalDisplacement;
	y += collision.horizontalDisplacement;
	hAxis += collision.horizontalSpeed / maxSpeed;
	vAxis += collision.verticalSpeed / maxSpeed;
	angularVelocity += collision.spin / _collider->momentOfInertia;
}
bool GameObject::isValid() { return _valid; }
void GameObject::inValidate() { _valid = false; }
GameObject::~GameObject() {
	delete _collider;
}
void GameObject::Damage(float amount) {
	hp -= amount;
	if (hp <= 0) {
		Kill();
	}
}
void GameObject::Kill() {
	if (corpseLifeTime > 0) {
		CorpseObject::createFromObject(GetSim(), this);
	}
	_sim->despawnUnit(_id);
}
bool GameObject::isPlayer() {
	return false;
}