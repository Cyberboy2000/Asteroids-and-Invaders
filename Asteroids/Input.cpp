#include "SFML/Window/Keyboard.hpp"
#include "Input.h"
#include <cmath>
#include <vector>
#include <string>
#include <map>

namespace {
	std::map<sf::Keyboard::Key, std::vector<Input::Listener*>*> listeners{};
	//std::map<sf::Keyboard::Key, bool> keys;
}

bool Input::AttackButtonDown() {
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

float Input::HorizontalAxis() {
	float value = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		value -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		value += 1;
	}

	return value;
};

float Input::VerticalAxis() {
	float value = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		value -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		value += 1;
	}

	return value;
};

float Input::AxesMagnitude() {
	float h = HorizontalAxis();
	float v = VerticalAxis();

	return sqrt(h * h + v * v);
}

float Input::AxesMagnitude(float h, float v) {
	return sqrt(h * h + v * v);
}

float Input::HorizontalAxisNormalized() {
	float h = HorizontalAxis();
	float v = VerticalAxis();
	float magnitude = AxesMagnitude(h, v);

	if (magnitude > 1) {
		h = h / magnitude;
	}
	return h;
}

float Input::VerticalAxisNormalized() {
	float h = HorizontalAxis();
	float v = VerticalAxis();
	float magnitude = AxesMagnitude(h, v);

	if (magnitude > 1) {
		v = v / magnitude;
	}
	return v;
}

void Input::RemoveListener(Listener* t, sf::Keyboard::Key key) {
	if (listeners.contains(key)) {
		std::vector<Listener*>* vec = listeners[key];
		for (int i = vec->size() - 1; i >= 0; i--) {
			Listener* listener = (*vec)[i];
			if (listener == t) {
				vec->erase(vec->begin() + i);
				return;
			}
		}
	}
}

void Input::RegisterListener(Listener* t, sf::Keyboard::Key key) {
	if (listeners.contains(key)) {
		std::vector<Listener*>* vec = listeners[key];
		for (int i = vec->size() - 1; i >= 0; i--) {
			Listener* listener = (*vec)[i];
			if (listener == t) {
				return;
			}
		}
	} else {
		listeners[key] = new std::vector<Listener*>();
	}

	listeners[key]->push_back(t);
	//keys[key] = sf::Keyboard::isKeyPressed(key);
}

void Input::Tick() {
	/*for (auto item : keys) {
		auto key = item.first;
		bool pressed = sf::Keyboard::isKeyPressed(key);
		if (pressed != item.second) {
			keys[key] = pressed;
			if (pressed) {
				for (Listener* listener : *listeners[key]) {
					listener->onKeyPressed(key);
				}
			}
		}
	}*/
}

void Input::OnKeyPressed(sf::Keyboard::Key key) {
	if (listeners.contains(key)) {
		for (Listener* listener : *listeners[key]) {
			listener->onKeyPressed(key);
		}
	}
}