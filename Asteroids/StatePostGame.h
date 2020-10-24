#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "State.h"
#include "Input.h"

namespace StateManager {
	class StatePostGame : public State, Input::Listener
	{
	public:
		/// <summary>
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
		StatePostGame();
		/// <summary>
		/// Returns the static instance of this state.
		/// </summary>
		static StatePostGame* state()
		{
			static StatePostGame* instance = new StatePostGame();
			return instance;
		}

		sf::Font* font;
		sf::Text* gameOverTxt;
		sf::Text* continueTxt;
		int gameOverFontSize = 100;
		int continueFontSize = 50;
		int rowSpace = 15;
	private:
		sf::RenderWindow* _window;
	};
}
