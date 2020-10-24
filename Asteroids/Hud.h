#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"

namespace client {
	class Hud
	{
	public:
		Hud(sf::RenderWindow* window, sim::Game* sim);
		~Hud();
		/// <summary>
		/// Render a frame to the window.
		/// </summary>
		void Render();
		/// <summary>
		/// Screen to render to.
		/// </summary>
		sf::RenderWindow* window;
		sim::Game* _sim;
		sf::Font* font;
		sf::Text* playerHealth;
		sf::Text* playerScore;
		sf::Text* difficultyText;
		float playerHealthX = 100;
		float playerHealthY = 100;
		float playerScoreX = 100;
		float playerScoreY = 100;
		int fontSize = 100;

		//NonCopyable
		Hud(const Hud&) = delete;
		//NonCopyable
		void operator=(const Hud&) = delete;
	};
}