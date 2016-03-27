#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "World.h"

int main()
{
	std::shared_ptr<sf::RenderWindow> window(new sf::RenderWindow(sf::VideoMode(1280, 768), "Steering Behaviour"));
	window->setVerticalSyncEnabled(true);

	World world(window);
	world.run();

}
