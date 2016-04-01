#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "SceneHandler.h"
#include "ViewHandler.h"

class EventHandler
{
public:
	EventHandler(std::shared_ptr<sf::RenderWindow> window, SceneHandler* sceneHandler, ViewHandler* viewHandler, Behaviours* behaviours);
	
	void	update();

private:
	void	onKeyPressed(int key);
	void	onMouseMoved(int mouseX, int mouseY);

private:
	std::shared_ptr<sf::RenderWindow>	m_window;
	SceneHandler*						m_sceneHandler;
	ViewHandler*						m_viewHandler;
	Behaviours*							m_behaviours;
};

