#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "State.h"

namespace StateManager
{
	/// <summary>
	/// Adds a game state to the top of the state stack.
	/// </summary>
	void Activate(State* state);
	/// <summary>
	/// Removes a game state from the state stack.
	/// </summary>
	void Deactivate(State* state);
	/// <summary>
	/// Returns true if the given state exists in the state stack.
	/// </summary>
	bool IsActive(State* state);
	/// <summary>
	/// Returns the top of the state stack.
	/// </summary>
	State* GetFocused();
	/// <summary>
	/// Sets up the state manager to use the window.
	/// </summary>
	void Start(sf::RenderWindow* window);
	/// <summary>
	/// Handle Exception.
	/// </summary>
	void OnException(const std::string& ex);
	/// <summary>
	/// Master loop, handling all game logic and rendering.
	/// </summary>
	void MainLoop();
	void SetTimeScale(float f);
	float GetTimeScale();
};

