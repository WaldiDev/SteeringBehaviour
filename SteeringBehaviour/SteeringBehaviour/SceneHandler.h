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
	void	draw();
	void	addUnit(std::shared_ptr<IBehaviour> behaviour);

	sf::Vector2f	getMousePos() const;
	void			setMousePos(sf::Vector2f mousePos);

private:
	std::shared_ptr<sf::RenderWindow>	m_window;
	std::vector<std::shared_ptr<Unit>>	m_unitObjects;
	sf::Texture							m_unitTexture;
	sf::Vector2f						m_mousePos;
};

