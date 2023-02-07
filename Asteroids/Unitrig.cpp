#include "Boardrig.h"
#include "Unitrig.h"
#include "GameObject.h"
#include "Invader.h"
#include <SFML/Graphics.hpp>

using namespace client;

void Unitrig::Render() {
	if (_obj->isVisible) {
		_sprite->setPosition(_board->WorldToScreen(_obj->x, _obj->y));
		_sprite->setColor(_obj->color);
		float angle = _board->worldToSpriteAngle(_obj->angle);
		_sprite->setRotation(angle);
		_board->window->draw(*_sprite);
	}
}

Unitrig::Unitrig(Boardrig* board, sim::GameObject* obj) : _obj(obj), _board(board), _sprite(new sf::Sprite) {
	sf::Texture* texture = board->getTexture(obj->textureFile);
	_sprite->setTexture(*texture);
	sf::Vector2u size = texture->getSize();

	_sprite->setOrigin(size.x * 0.5f,size.y * 0.5f);
	board->scaleSprite(_sprite);
	_sprite->setTextureRect(sf::IntRect(0, 0, size.x, size.y));

	sim::Collider* collider = _obj->GetCollider();
	if (collider != nullptr) {
		_collider = new sf::CircleShape(collider->mainRadius);
		_collider->setOrigin(sf::Vector2f(collider->mainRadius, collider->mainRadius));
	}
}

void Unitrig::DebugRender() {
	if (_collider != nullptr) {
		sim::Collider* collider = _obj->GetCollider();
		_collider->setFillColor(sf::Color(255, 0, 255, 127));
		if (collider->currentCollision.isKinetic) {
			_collider->setFillColor(sf::Color(255, 0, 0, 127));
		} else if (collider->currentCollision.isPhysicsCollision) {
			_collider->setFillColor(sf::Color(255, 255, 0, 127));
		} else if (collider->currentCollision.isCollision) {
			_collider->setFillColor(sf::Color(0, 255, 255, 127));
		}
		_collider->setPosition(_board->WorldToScreen(_obj->x, _obj->y));
		_board->window->draw(*_collider);
	}

	sf::Vertex line[] =
	{
		sf::Vertex(_board->WorldToScreen(_obj->x, _obj->y), sf::Color(0, 255, 255, 127)),
		sf::Vertex(_board->WorldToScreen(_obj->x + _obj->hAxis * _obj->maxSpeed, _obj->y + _obj->vAxis * _obj->maxSpeed), sf::Color(0, 255, 255, 127))
	};

	_board->window->draw(line, 2, sf::Lines);

	sim::Invader* invader = dynamic_cast<sim::Invader*>(_obj);

	if (invader != 0) {
		line[0] = sf::Vertex(_board->WorldToScreen(_obj->x, _obj->y), sf::Color(10, 255, 0, 127));

		float x = 0;
		float y = 0;

		for (int i = 0; i < invader->aiForces->size(); i += 2) {
			line[1] = sf::Vertex(_board->WorldToScreen(_obj->x + invader->aiForces->at(i), _obj->y + invader->aiForces->at(i + 1)), sf::Color(10, 255, 0, 127));
			x += invader->aiForces->at(i);
			y += invader->aiForces->at(i + 1);

			_board->window->draw(line, 2, sf::Lines);
		}

		line[0] = sf::Vertex(_board->WorldToScreen(_obj->x, _obj->y), sf::Color(255, 15, 0, 127));
		line[1] = sf::Vertex(_board->WorldToScreen(_obj->x + x, _obj->y + y), sf::Color(255, 15, 0, 127));

		_board->window->draw(line, 2, sf::Lines);
	}
}

Unitrig::~Unitrig() {
	delete _sprite;
	delete _collider;
}