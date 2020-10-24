#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <typeinfo>
#include <cmath>
#include "Util.h"
#include "Boardrig.h"
#include "SimEvent.h"
#include "Config.h"
#include "GameObject.h"
#include "RigType.h"

#define RAD_TO_DEG static_cast<float>(57.295779513)

client::Boardrig::Boardrig(sf::RenderWindow* _window, sim::Game* _sim) : window(_window), sim(_sim), rigs() {
	//Keep track of window size so we can check for resizing.
	sf::Vector2u windowSize = window->getSize();

	_halfW = sim->boardW * 0.5f;
	_halfH = sim->boardH * 0.5f;

	sf::FloatRect viewArea(0, 0, static_cast<float>(sim->boardW), static_cast<float>(sim->boardH));
	window->setView(sf::View(viewArea));
	_bg = new sf::Sprite(*getTexture("Sprites/Bg.png"));

	Input::RegisterListener(this, sf::Keyboard::H);
}

client::Boardrig::~Boardrig() {
	for (auto obj : rigs)
	{
		delete obj.second;
	}
	for (auto obj : _loadedTextures)
	{
		delete obj.second;
	}
	delete _bg;

	Input::RemoveListener(this, sf::Keyboard::H);
}

void client::Boardrig::onSimEvent(const SimEvent ev) {
	if (ev.evType == SimEvent::unitCreated) {
		sim::GameObject* obj = sim->gameObjects[ev.unitId];
		if (obj != nullptr && (obj->rigType == RigType::unitrig)) {
			Unitrig* rig = new Unitrig{ this, obj };
			rigs[ev.unitId] = rig;
		}
	} else if (ev.evType == SimEvent::unitDestroyed) {
		if (rigs[ev.unitId] != nullptr) {
			delete rigs[ev.unitId];
			rigs.erase(ev.unitId);
		}
	}
}

void client::Boardrig::onKeyPressed(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::H) {
		_debugging = !_debugging;
	}
}

/*void client::Boardrig::updateRatios() {
	sf::Vector2u size = window->getSize();
	int dx = size.x - prevW;
	int dy = size.y - prevH;

	prevH = size.y;
	prevW = size.x;

	int ax = abs(dx);
	int ay = abs(dy);

	if (Config::fixedAspect) {
		if (ax > ay) {
			//Width changed, update height
			prevH = static_cast<unsigned int>(prevW * Config::invAspectRatio());
			window->setSize(sf::Vector2u{ prevW, prevH });
			ay = 1;//Just so that we update the world to screen ratio
		}
		else if (ay > 0) {
			//Height changed, update width
			prevW = static_cast<unsigned int>(prevH * Config::aspectRatio());
			window->setSize(sf::Vector2u{ prevW, prevH });
			ax = 1;//Just so that we update the world to screen ratio
		}
	}

	if (ax > 0) {
		worldToScreenX = (float)prevW / (float)sim->boardW;
		halfW = prevW * 0.5f;
	}
	if (ay > 0) {
		worldToScreenY = (float)prevH / (float)sim->boardH;
		halfH = prevH * 0.5f;
	}
}*/

void client::Boardrig::updateRatios() {
	sf::Vector2u windowSize = window->getSize();
	if (_prevW != windowSize.x || _prevH != windowSize.y) {
		_prevW = windowSize.x;
		_prevH = windowSize.y;

		sf::View view = window->getView();
		float windowAspect = (float)_prevW / (float)_prevH;
		float gameAspect = (float)sim->boardW / (float)sim->boardH;
		if (windowAspect > gameAspect) {
			float viewPortW = gameAspect / windowAspect;
			float viewPortX = 0.5f * (1 - viewPortW);
			view.setViewport(sf::FloatRect(viewPortX, 0, viewPortW, 1));
		} else {
			float viewPortH = windowAspect / gameAspect;
			float viewPortY = 0.5f * (1 - viewPortH);
			view.setViewport(sf::FloatRect(0, viewPortY, 1, viewPortH));
		}
		window->setView(view);
	}
}

void client::Boardrig::Render() {
	updateRatios();

	window->draw(*_bg);

	for (auto rig : rigs) {
		rig.second->Render();
	}
	if (_debugging) {
		for (auto rig : rigs) {
			rig.second->DebugRender();
		}
	}
}

sf::Vector2f client::Boardrig::WorldToScreen(float x, float y) {
	//World origin is in screen center and points y up, screen origin is top left and points y down.
	return sf::Vector2f{ x + _halfW, -y + _halfH };
}

void client::Boardrig::scaleSprite(sf::Sprite* sprite) {
	//sprite->setScale(worldToScreenX, worldToScreenY);
}

float client::Boardrig::worldToSpriteAngle(float worldAngle) {
	return 360 - (worldAngle * RAD_TO_DEG);
}

sf::Texture* client::Boardrig::getTexture(std::string name) {
	if (_loadedTextures.count(name) > 0) {
		return _loadedTextures[name];
	} else {
		sf::Texture* texture = new sf::Texture;
		texture->loadFromFile(name);
		texture->setSmooth(true);
		_loadedTextures[name] = texture;
		return texture;
	}
}