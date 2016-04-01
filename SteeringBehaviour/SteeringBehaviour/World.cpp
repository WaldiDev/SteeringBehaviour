#include "World.h"

World::World(std::shared_ptr<sf::RenderWindow> window)
	: m_window(window)	
	, m_viewHandler(window)
	, m_sceneHandler(window)
	, m_behaviours(new Behaviours(&m_sceneHandler))
	, m_eventHandler(window, &m_sceneHandler, &m_viewHandler, m_behaviours)
{
}

void World::run()
{
	sf::Clock clock;
	while(m_window->isOpen())
	{
		auto delta = clock.restart().asSeconds();
		update(delta);
		draw();
	}
}

void World::update(float delta)
{
	m_eventHandler.update();
	m_sceneHandler.update(delta);
}

void World::draw()
{
	m_window->clear(sf::Color(128,128,128));
	m_sceneHandler.draw();
	m_viewHandler.draw();
	m_window->display();
}
