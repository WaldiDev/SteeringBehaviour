#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "IBehaviour.h"

class Unit
{
public:
	explicit Unit(std::shared_ptr<IBehaviour> behavior, sf::Sprite sprite);
	~Unit();

	void	init();
	void	update(float delta);
	void	draw(const sf::RenderWindow& window);

	void	setBehaviour(std::shared_ptr<IBehaviour> behavior);

private:
	std::shared_ptr<IBehaviour>	m_behaviour;
	sf::Vector2f				m_position;
	sf::Vector2f				m_velocity;
	float						m_maxVelocity;
	sf::Sprite					m_sprite;
};

