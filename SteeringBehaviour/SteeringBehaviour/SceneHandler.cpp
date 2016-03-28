#include "SceneHandler.h"

SceneHandler::SceneHandler(std::shared_ptr<sf::RenderWindow> window)
	: m_window(window)
{
	m_unitTexture.loadFromFile("unit.png");
}

void SceneHandler::update(float delta)
{
	for (auto unit : m_unitObjects)
	{
		unit->update(delta);
	}
}

void SceneHandler::addUnit(std::shared_ptr<IBehaviour> behaviour)
{
	std::shared_ptr<Unit> unit(new Unit(behaviour, sf::Sprite(m_unitTexture, sf::IntRect(0, 0, 32, 32))));
	m_unitObjects.push_back(unit);
}
