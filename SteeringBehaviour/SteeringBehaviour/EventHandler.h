#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "SceneHandler.h"
class EventHandler
{
public:
	EventHandler(std::shared_ptr<sf::RenderWindow> window, SceneHandler& sceneHandler);
	
	void	update();

private:
	void	onKeyPressed(int key);

private:
	std::shared_ptr<sf::RenderWindow>	m_window;
	SceneHandler						m_sceneHandler;
};

