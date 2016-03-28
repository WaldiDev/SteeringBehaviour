#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Unit.h"

class SceneHandler
{
public:
	explicit SceneHandler(std::shared_ptr<sf::RenderWindow> window);
	void	update(float delta);
	void	addUnit(std::shared_ptr<IBehaviour> behaviour);

private:
	std::shared_ptr<sf::RenderWindow>	m_window;
	std::vector<std::shared_ptr<Unit>>	m_unitObjects;
	sf::Texture							m_unitTexture;
};

