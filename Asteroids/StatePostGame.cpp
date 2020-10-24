#include "StatePostGame.h"
#include "StateMainMenu.h"
#include "SFML/Graphics.hpp"
#include "StateGame.h"
#include "StateManager.h"
#include "Input.h"
#include "Strings.h"

using namespace StateManager;

void StatePostGame::Update(float deltaTime) {
	sf::View view = _window->getView();
	sf::Vector2f size = view.getSize();
	sf::Vector2f center = view.getCenter();
	gameOverTxt->setPosition(center.x - 0.5f * gameOverTxt->getLocalBounds().width, center.y - gameOverTxt->getLocalBounds().height - rowSpace);
	continueTxt->setPosition(center.x - 0.5f * continueTxt->getLocalBounds().width, center.y + rowSpace);
	_window->draw(*gameOverTxt);
	_window->draw(*continueTxt);
}
void StatePostGame::OnUnLoad() {
	Input::RemoveListener(this, sf::Keyboard::Escape);
	Input::RemoveListener(this, sf::Keyboard::Space);
}
void StatePostGame::OnLoad(sf::RenderWindow* window) {
	_window = window;
	Input::RegisterListener(this, sf::Keyboard::Escape);
	Input::RegisterListener(this, sf::Keyboard::Space);
}
void StatePostGame::onKeyPressed(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::Escape) {
		StateManager::Deactivate(this);
		StateManager::Deactivate(StateGame::state());
		StateManager::Activate(StateMainMenu::state());
	} else if (key == sf::Keyboard::Space) {
		StateManager::Deactivate(this);
		StateGame::state()->restart();
	}
}

StatePostGame::StatePostGame() {
	font = new sf::Font();
	font->loadFromFile("Arial.ttf");
	gameOverTxt = new sf::Text();
	continueTxt = new sf::Text();
	gameOverTxt->setFont(*font);
	continueTxt->setFont(*font);
	gameOverTxt->setCharacterSize(gameOverFontSize);
	continueTxt->setCharacterSize(continueFontSize);
	gameOverTxt->setString(Strings::PostGame::GAMEOVER);
	continueTxt->setString(Strings::PostGame::CONTINUEORQUIT);
	gameOverTxt->setFillColor(sf::Color::White);
	continueTxt->setFillColor(sf::Color::White);
}