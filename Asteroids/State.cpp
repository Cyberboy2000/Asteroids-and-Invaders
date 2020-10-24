#include "State.h"

using namespace StateManager;

State::State() {

}
void State::OnFocus() {}
void State::OnLoseFocus() {}
void State::Focus() {
	focused = true;
	OnFocus();
}
void State::LoseFocus() {
	focused = false;
	OnLoseFocus();
}
void State::Load(sf::RenderWindow* window) {
	if (!loaded) {
		loaded = true;
		OnLoad(window);
	}
}
void State::UnLoad() {
	if (loaded) {
		loaded = false;
		OnUnLoad();
	}
}

bool State::isLoaded() {
	return loaded;
}

bool State::isFocused() {
	return focused;
}