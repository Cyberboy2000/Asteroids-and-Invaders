#include "StateMainMenu.h"
#include "SFML/Graphics.hpp"
#include "StateDifficultySelection.h"
#include "StateGame.h"
#include "StateManager.h"
#include "Input.h"
#include "Strings.h"

using namespace StateManager;

void StateMainMenu::Update(float deltaTime) {
	_window->draw(*_bg);

	sf::View view = _window->getView();
	sf::Vector2u windowSize = _window->getSize();
	if (_prevW != windowSize.x || _prevH != windowSize.y) {
		_prevW = windowSize.x;
		_prevH = windowSize.y;

		float windowAspect = (float)_prevW / (float)_prevH;
		float gameAspect = screenWidth / screenHeight;
		if (windowAspect > gameAspect) {
			float viewPortW = gameAspect / windowAspect;
			float viewPortX = 0.5f * (1 - viewPortW);
			view.setViewport(sf::FloatRect(viewPortX, 0, viewPortW, 1));
		} else {
			float viewPortH = windowAspect / gameAspect;
			float viewPortY = 0.5f * (1 - viewPortH);
			view.setViewport(sf::FloatRect(0, viewPortY, 1, viewPortH));
		}
		_window->setView(view);
	}

	sf::Vector2f size = view.getSize();
	sf::Vector2f center = view.getCenter();

	float y = center.y - 0.5f * (options[0]->getLocalBounds().height + rowSpace) * (options.size() - 1);
	if (isFocused()) {
		_bob += deltaTime * cursorBobSpeed;
	}

	int i = 0;
	for (auto textObj : options) {
		sf::FloatRect textSize = textObj->getLocalBounds();
		textObj->setOrigin(textSize.left + textSize.width * 0.5f, textSize.top + textSize.height * 0.5f);
		textObj->setPosition(center.x,y);
		_window->draw(*textObj);
		if (i == _optionIndex) {
			cursor->setPosition(center.x + (sinf(_bob) - 1) * cursorBob - 0.5f * textSize.width, y);
			_window->draw(*cursor);
		}

		y += rowSpace + textSize.height;
		i++;
	}
}
void StateMainMenu::OnUnLoad() {
	Input::RemoveListener(this, sf::Keyboard::Up);
	Input::RemoveListener(this, sf::Keyboard::Down);
	Input::RemoveListener(this, sf::Keyboard::W);
	Input::RemoveListener(this, sf::Keyboard::S);
	Input::RemoveListener(this, sf::Keyboard::Enter);
	Input::RemoveListener(this, sf::Keyboard::Space);
}
void StateMainMenu::OnLoad(sf::RenderWindow* window) {
	_window = window;
	window->setTitle(Strings::TITLE);
	sf::FloatRect viewArea(0, 0, screenWidth, screenHeight);
	window->setView(sf::View(viewArea));
	_bob = 0;
	_optionIndex = 0;
	_prevW = 0;
	_prevH = 0;
	Input::RegisterListener(this, sf::Keyboard::Up);
	Input::RegisterListener(this, sf::Keyboard::Down);
	Input::RegisterListener(this, sf::Keyboard::W);
	Input::RegisterListener(this, sf::Keyboard::S);
	Input::RegisterListener(this, sf::Keyboard::Enter);
	Input::RegisterListener(this, sf::Keyboard::Space);
}

void StateMainMenu::onKeyPressed(sf::Keyboard::Key key) {
	if (isFocused()) {
		if (key == sf::Keyboard::Up || key == sf::Keyboard::W) {
			_optionIndex--;
			if (_optionIndex < 0) {
				_optionIndex = options.size() - 1;
			}
		}
		else if (key == sf::Keyboard::Down || key == sf::Keyboard::S) {
			_optionIndex++;
			if (_optionIndex >= options.size()) {
				_optionIndex = 0;
			}
		}
		else if (key == sf::Keyboard::Enter || key == sf::Keyboard::Space) {
			if (_optionIndex < options.size() - 1) {
				StateGame* game = StateManager::StateGame::state();
				game->SetGameMode(_optionIndex);
				StateDifficultySelection* selection = StateDifficultySelection::state();
				StateManager::Activate(selection);
			} else {
				StateManager::Deactivate(this);
			}
		}
	}
}

StateMainMenu::StateMainMenu() {
	font = new sf::Font();
	font->loadFromFile("Arial.ttf");
	cursorTexture = new sf::Texture;
	cursorTexture->loadFromFile("Sprites/MenuCursor.png");
	cursor = new sf::Sprite(*cursorTexture);
	//options.push_back(new sf::Text(Strings::Menu::EASY, *font, fontSize));
	//options.push_back(new sf::Text(Strings::Menu::MEDIUM, *font, fontSize));
	//options.push_back(new sf::Text(Strings::Menu::HARD, *font, fontSize));
	options.push_back(new sf::Text(Strings::Menu::ASTEROIDS, *font, fontSize));
	options.push_back(new sf::Text(Strings::Menu::INVADERS, *font, fontSize));
	options.push_back(new sf::Text(Strings::Menu::QUIT, *font, fontSize));
	sf::FloatRect size = cursor->getLocalBounds();
	cursor->setOrigin(size.width, size.height * 0.5f);
	_bgTex = new sf::Texture;
	_bgTex->loadFromFile("Sprites/MenuBg.png");
	_bg = new sf::Sprite(*_bgTex);
}

void StateMainMenu::OnFocus() {
	for (auto textObj : options) {
		textObj->setFillColor(enabledColor);
		textObj->setOutlineColor(sf::Color::Black);
		textObj->setOutlineThickness(outLineThickness);
	}
	cursor->setColor(enabledColor);
}

void StateMainMenu::OnLoseFocus() {
	for (auto textObj : options) {
		textObj->setFillColor(disabledColor);
	}
	cursor->setColor(disabledColor);
}