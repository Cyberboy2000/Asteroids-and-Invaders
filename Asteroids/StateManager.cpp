#include "StateManager.h"
#include "SFML/Graphics.hpp"
#include "Input.h"
#include <vector>

namespace StateManager {
	namespace {
		std::vector<State*> states;
		State* focused = nullptr;
		sf::RenderWindow* _window;
	}
	
	void Activate(State* state) {
		if (!IsActive(state)) {
			states.push_back(state);
			state->Load(_window);
			if (focused != nullptr) {
				focused->LoseFocus();
			}
			focused = state;
			state->Focus();
		}
	}

	void Deactivate(State* state) {
		for (int i = states.size() - 1; i >= 0; i--) {
			State* foundState = states[i];
			if (foundState == state) {
				if (state->isFocused()) {
					state->LoseFocus();
				}
				state->UnLoad();
				states.erase(states.begin() + i);
				if (state == focused) {
					if (states.size() == 0) {
						focused = nullptr;
					} else {
						focused = states.back();
						focused->Focus();
					}
				}
				break;
			}
		}
	}

	bool IsActive(State* state) {
		for (int i = 0; i < states.size(); i++) {
			if (states[i] == state) {
				return true;
			}
		}

		return false;
	}

	State* GetFocused() {
		return focused;
	}

	void Start(sf::RenderWindow* window) {
		_window = window;
	}

	void OnException(const std::string& ex) {
		std::string str = "Exception Thrown:\n" + ex;
		printf(str.c_str());
		printf("\n");
		
		sf::Font font{};
		font.loadFromFile("Arial.ttf");
		sf::Text text(str, font, 100);
		sf::Vector2f center = _window->getView().getCenter();
		sf::FloatRect textSize = text.getLocalBounds();
		text.setOrigin(textSize.left + textSize.width * 0.5f, textSize.top + textSize.height * 0.5f);
		text.setPosition(center.x, center.y);
		text.setFillColor(sf::Color::Magenta);
		_window->draw(text);
		_window->display();

		sf::Event event;
		while (true) {
			if (_window->pollEvent(event) && (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed)) {
				return;
			}
		}
	}

	void MainLoop() {
		try {
			sf::Clock clock{};

			while (_window->isOpen() && states.size() > 0) {
				_window->clear();
				sf::Event event;
				while (_window->pollEvent(event)) {
					if (event.type == sf::Event::Closed) {
						return;
					}
					else if (event.type == sf::Event::KeyPressed) {
						Input::OnKeyPressed(event.key.code);
					}
				}

				float deltaTime = clock.restart().asSeconds();
				Input::Tick();

				std::vector<State*> temp = states;

				for (int i = 0; i < temp.size(); i++) {
					State* state = temp[i];
					if (state->isLoaded()) {
						state->Update(deltaTime);
					}
				}

				_window->display();
			}
		} catch (std::exception* ex) {
			OnException(ex->what());
		}
		catch (std::exception ex) {
			OnException(ex.what());
		}
		catch (std::string ex) {
			OnException(ex);
		}
		catch (int ex) {
			OnException("Exception " + std::to_string(ex));
		}
		catch (...) {
			OnException("Unknown Exception");
		}
	}
}