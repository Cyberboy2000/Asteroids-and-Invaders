#include "Hud.h"
#include "Game.h"
#include "GameObject.h"
#include "PlayerObject.h"
#include "Strings.h"
#include <string>

using namespace client;

std::string GetDifficultyString(int idx) {
	switch (idx) {
	case 0: return Strings::UI::ASTEROIDS_EASY;
	case 1: return Strings::UI::ASTEROIDS_MEDIUM;
	case 2: return Strings::UI::ASTEROIDS_HARD;
	case 3: return Strings::UI::INVADERS_EASY;
	case 4: return Strings::UI::INVADERS_MEDIUM;
	case 5: return Strings::UI::INVADERS_HARD;
	}
}

Hud::Hud(sf::RenderWindow* _window, sim::Game* sim) : window(_window), _sim(sim) {
	font = new sf::Font();
	font->loadFromFile("Arial.ttf");
	playerHealth = new sf::Text();
	playerScore = new sf::Text();
	difficultyText = new sf::Text();
	playerHealth->setFont(*font);
	playerScore->setFont(*font);
	difficultyText->setFont(*font);
	playerHealth->setCharacterSize(fontSize);
	playerScore->setCharacterSize(fontSize);
	difficultyText->setCharacterSize(fontSize);
	playerHealth->setFillColor(sf::Color::White);
	playerScore->setFillColor(sf::Color::White);
	difficultyText->setFillColor(sf::Color::White);
	difficultyText->setString(GetDifficultyString(_sim->GetParams()->difficultyIndex));
	_window->setTitle(GetDifficultyString(_sim->GetParams()->difficultyIndex));
}

Hud::~Hud() {
	delete font;
	delete playerHealth;
	delete playerScore;
	delete difficultyText;
}

void Hud::Render() {
	if (!_sim->isFinished()) {
		sf::View view = window->getView();
		sf::Vector2f size = view.getSize();
		sf::Vector2f center = view.getCenter();
		auto player = _sim->GetPlayer();
		playerHealth->setString(Strings::UI::HP + std::to_string((int)player->hp));
		playerScore->setString(Strings::UI::SCORE + std::to_string(player->score));
		playerHealth->setPosition(center.x - 0.5f * size.x + playerHealthX, center.y - 0.5f * size.y + playerHealthY);
		playerScore->setPosition(center.x + 0.5f * size.x - playerScoreX - playerScore->getLocalBounds().width, center.y - 0.5f * size.y + playerScoreY);
		difficultyText->setPosition(center.x + 0.5f * size.x - playerScoreX - difficultyText->getLocalBounds().width, center.y + 0.5f * size.y - playerScoreY - difficultyText->getLocalBounds().height);
	} else {
		playerHealth->setString(Strings::UI::HP + "0");
	}

	window->draw(*playerHealth);
	window->draw(*playerScore);
	window->draw(*difficultyText);
}