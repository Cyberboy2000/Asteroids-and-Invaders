#pragma once
#include "SFML/Window/Keyboard.hpp"

namespace Input
{
	class Listener {
	public:
		/// <summary>
		/// Callback function for registering input listeners, triggers on the first frame a key is pressed down.
		/// </summary>
		virtual void onKeyPressed(sf::Keyboard::Key key) = 0;
	};

	/// <summary>
	/// Returns true every frame the attack button is held down.
	/// </summary>
	bool AttackButtonDown();
	/// <summary>
	/// Returns the horizontal axis as a float between -1 (left) and 1 (right).
	/// </summary>
	float HorizontalAxis();
	/// <summary>
	/// Returns the vertical axis as a float between -1 (down) and 1 (up).
	/// </summary>
	float VerticalAxis();
	/// <summary>
	/// Returns the magnitude of the horizontal and vertical axes combined.
	/// </summary>
	float AxesMagnitude();
	/// <summary>
	/// Returns the magnitude of the horizontal and vertical axes combined.
	/// </summary>
	float AxesMagnitude(float h, float v);
	/// <summary>
	/// Returns the horizontal axis as a float, normalized so that the magnitude of the horizontal and vertical axes together is at most 1.
	/// </summary>
	float HorizontalAxisNormalized();
	/// <summary>
	/// Returns the vertical axis as a float, normalized so that the magnitude of the horizontal and vertical axes together is at most 1.
	/// </summary>
	float VerticalAxisNormalized();
	/// <summary>
	/// Register a listener for a keyboard press.
	/// </summary>
	void RegisterListener(Listener* t, sf::Keyboard::Key key);
	/// <summary>
	/// Unregisters a registred listener.
	/// </summary>
	void RemoveListener(Listener* t, sf::Keyboard::Key key);
	/// <summary>
	/// Updates and sends keyboard states to listener.
	/// </summary>
	void Tick();
	void OnKeyPressed(sf::Keyboard::Key key);
};

