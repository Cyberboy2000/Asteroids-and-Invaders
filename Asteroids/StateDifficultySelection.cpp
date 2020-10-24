#include "StateDifficultySelection.h"
#include "StateMainMenu.h"
#include "SFML/Graphics.hpp"
#include "StateGame.h"
#include "StateManager.h"
#include "Input.h"
#include "Strings.h"

using namespace StateManager;

void StateDifficultySelection::Update(float deltaTime) {
	sf::View view = _window->getView();
	sf::Vector2f size = view.getSize();
	sf::Vector2f center = view.getCenter();

	float y = center.y - 0.5f * (options[0]->getLocalBounds().height + rowSpace) * (options.size() - 1);
	_bob += deltaTime * cursorBobSpeed;

	int i = 0;
	for (auto textObj : options) {
		sf::FloatRect textSize = textObj->getLocalBounds();
		textObj->setOrigin(textSize.left + textSize.width * 0.5f, textSize.top + textSize.height * 0.5f);
		textObj->setPosition(center.x, y);
		_window->draw(*textObj);
		if (i == _optionIndex) {
			cursor->setPosition(center.x + (sinf(_bob) - 1) * cursorBob - 0.5f * textSize.width, y);
			_window->draw(*cursor);
		}

		y += rowSpace + textSize.height;
		i++;
	}
}
void StateDifficultySelection::OnUnLoad() {
	Input::RemoveListener(this, sf::Keyboard::Up);
	Input::RemoveListener(this, sf::Keyboard::Down);
	Input::RemoveListener(this, sf::Keyboard::W);
	Input::RemoveListener(this, sf::Keyboard::S);
	Input::RemoveListener(this, sf::Keyboard::Enter);
	Input::RemoveListener(this, sf::Keyboard::Space);
}
void StateDifficultySelection::OnLoad(sf::RenderWindow* window) {
	_window = window;
	_bob = 0;
	_optionIndex = 0;
	Input::RegisterListener(this, sf::Keyboard::Up);
	Input::RegisterListener(this, sf::Keyboard::Down);
	Input::RegisterListener(this, sf::Keyboard::W);
	Input::RegisterListener(this, sf::Keyboard::S);
	Input::RegisterListener(this, sf::Keyboard::Enter);
	Input::RegisterListener(this, sf::Keyboard::Space);
}

void StateDifficultySelection::onKeyPressed(sf::Keyboard::Key key) {
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
			StateManager::Deactivate(this);
			if (_optionIndex < options.size() - 1) {
				StateGame* game = StateManager::StateGame::state();
				StateMainMenu* menu = StateManager::StateMainMenu::state();
				game->SetDifficulty(_optionIndex);
				StateManager::Deactivate(menu);
				StateManager::Activate(game);
			}
		}
	}
}

StateDifficultySelection::StateDifficultySelection() {
	font = new sf::Font();
	font->loadFromFile("Arial.ttf");
	cursorTexture = new sf::Texture;
	cursorTexture->loadFromFile("Sprites/MenuCursor.png");
	cursor = new sf::Sprite(*cursorTexture);
	options.push_back(new sf::Text(Strings::Menu::EASY, *font, fontSize));
	options.push_back(new sf::Text(Strings::Menu::MEDIUM, *font, fontSize));
	options.push_back(new sf::Text(Strings::Menu::HARD, *font, fontSize));
	options.push_back(new sf::Text(Strings::Menu::CANCEL, *font, fontSize));
	for (auto textObj : options) {
		textObj->setFillColor(fontColor);
		textObj->setOutlineColor(sf::Color::Black);
		textObj->setOutlineThickness(outLineThickness);
	}
	sf::FloatRect size = cursor->getLocalBounds();
	cursor->setOrigin(size.width, size.height * 0.5f);
}