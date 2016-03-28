#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "ViewHandler.h"
#include "EventHandler.h"

class World
{
public:
	explicit World(std::shared_ptr<sf::RenderWindow> window);
	void run();

private:
	std::shared_ptr<sf::RenderWindow>	m_window;
	ViewHandler							m_viewHandler;
	SceneHandler						m_sceneHandler;
	EventHandler						m_eventHandler;

private:
	void	update(float delta);
	void	draw();
};

