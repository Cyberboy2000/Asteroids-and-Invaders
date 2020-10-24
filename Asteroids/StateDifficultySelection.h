#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "State.h"
#include <vector>
#include "Input.h"

namespace StateManager {
	class StateDifficultySelection : public State, Input::Listener
	{
	public:// <summary>
		/// Updates the state and advances it by a given amount in seconds.
		/// </summary>
		void Update(float deltaTime) override;
		/// <summary>
		/// Callback function for resetting the state when it's being removed from the state stack.
		/// </summary>
		void OnUnLoad() override;
		/// <summary>
		/// Sets the state up for adding to the state stack.
		/// </summary>
		void OnLoad(sf::RenderWindow* window) override;
		/// <summary>
		/// Callback function for registering input listeners, triggers on the first frame a key is pressed down.
		/// </summary>
		void onKeyPressed(sf::Keyboard::Key key) override;
		StateDifficultySelection();
		/// <summary>
		/// Returns the static instance of this state.
		/// </summary>
		static StateDifficultySelection* state()
		{
			static StateDifficultySelection* instance = new StateDifficultySelection();
			return instance;
		}

		sf::Font* font;
		sf::Sprite* cursor;
		sf::Texture* cursorTexture;
		sf::Color fontColor = sf::Color::White;
		std::vector<sf::Text*> options;
		unsigned int fontSize = 75;
		int rowSpace = 15;
		float outLineThickness = 5;
		float cursorBob = 5;
		float cursorBobSpeed = 6;
	private:
		sf::RenderWindow* _window;
		int _optionIndex = 0;
		float _bob = 0;
	};
};

