#pragma once
#include "SFML/Graphics/RenderWindow.hpp"

namespace StateManager {
	class State
	{
	public:
		/// <summary>
		/// Updates the state and advances it by a given amount in seconds.
		/// </summary>
		virtual void Update(float deltaTime) = 0;
		/// <summary>
		/// Callback function for resetting the state when it's being removed from the state stack.
		/// </summary>
		virtual void OnUnLoad() = 0;
		/// <summary>
		/// Callback function for setting the state up for use when it's being added to the state stack.
		/// </summary>
		virtual void OnLoad(sf::RenderWindow* window) = 0;
		/// <summary>
		/// Callback function for when this object is at the top of the state stack.
		/// </summary>
		virtual void OnFocus();
		/// <summary>
		/// Callback function for when this object is no longer at the top of the state stack.
		/// </summary>
		virtual void OnLoseFocus();
		/// <summary>
		/// Handles the state gaining focus by marking it and calling the respective callback function.
		/// </summary>
		void Focus();
		/// <summary>
		/// Handles the state losing focus by unmarking it and calling the respective callback function.
		/// </summary>
		void LoseFocus();
		/// <summary>
		/// Handles the state being added to the state stack by marking it and calling the respective callback function.
		/// </summary>
		void Load(sf::RenderWindow* window);
		/// <summary>
		/// Handles the state being removed from the state stack by unmarking it and calling the respective callback function.
		/// </summary>
		void UnLoad();
		/// <summary>
		/// Returns true if the state is currently in the state stack.
		/// </summary>
		bool isLoaded();
		/// <summary>
		/// Returns true if the state is currently on the top of the state stack.
		/// </summary>
		bool isFocused();
		State();
		//NonCopyable
		State(const State&) = delete;
		//NonCopyable
		void operator=(const State&) = delete;
	private:
		bool loaded = false;
		bool focused = false;
	};
}