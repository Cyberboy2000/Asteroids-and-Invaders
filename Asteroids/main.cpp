#include "StateManager.h"
#include "StateGame.h"
#include "StateMainMenu.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Config.h"
#include <vector>
#include <io.h>

int main() {
	//_CrtSetBreakAlloc(148);
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(Config::windowWidth, Config::windowHeight), Strings::TITLE, 7U);
	window->setFramerateLimit(Config::frameLimit);

	StateManager::Start(window);
	StateManager::Activate(StateManager::StateMainMenu::state());
	StateManager::MainLoop();

	window->close();
	delete window;

	return 0;
}