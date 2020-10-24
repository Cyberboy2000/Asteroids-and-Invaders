#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "State.h"
#include <vector>
#include "Input.h"

namespace StateManager {
	class StateMainMenu : public State, Input::Listener
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
		/// Callback function for when this object is at the top of the state stack.
		/// </summary>
		void OnFocus() override;
		/// <summary>
		/// Callback function for when this object is no longer at the top of the state stack.
		/// </summary>
		void OnLoseFocus() override;
		/// <summary>
		/// Callback function for registering input listeners, triggers on the first frame a key is pressed down.
		/// </summary>
		void onKeyPressed(sf::Keyboard::Key key) override;
		StateMainMenu();
		/// <summary>
		/// Returns the static instance of this state.
		/// </summary>
		static StateMainMenu* state()
		{
			static StateMainMenu* instance = new StateMainMenu();
			return instance;
		}

		sf::Font* font;
		sf::Sprite* cursor;
		sf::Texture* cursorTexture;
		sf::Color enabledColor = sf::Color::White;
		sf::Color disabledColor = sf::Color(255, 255, 255, 128);
		std::vector<sf::Text*> options;
		unsigned int fontSize = 75;
		float outLineThickness = 5;
		int rowSpace = 15;
		float screenWidth = 1200;
		float screenHeight = 900;
		float cursorBob = 5;
		float cursorBobSpeed = 6;
	private:
		sf::RenderWindow* _window;
		sf::Texture* _bgTex;
		sf::Sprite* _bg;
		unsigned int _prevW = 0;
		unsigned int _prevH = 0;
		int _optionIndex = 0;
		float _bob = 0;
	};
};

