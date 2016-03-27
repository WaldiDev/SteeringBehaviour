#include "World.h"

World::World(std::shared_ptr<sf::RenderWindow> window)
	: m_window(window)
	, m_viewHandler(window)
{
}

void World::run()
{
	sf::Clock clock;
	while(m_window->isOpen())
	{
		auto delta = clock.restart().asMicroseconds() / 1000000;
		update(static_cast<float>(delta));
		draw();
	}
}

void World::update(float delta)
{
}

void World::draw()
{
	m_window->clear();
	m_viewHandler.draw();
	m_window->display();
}