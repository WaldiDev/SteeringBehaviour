#include "ViewHandler.h"


ViewHandler::ViewHandler(std::shared_ptr<sf::RenderWindow> window)
	: m_window(window)
	, m_fps(0)
{
	m_font.loadFromFile("tahoma.ttf");
	m_infoText.setFont(m_font);
	m_infoText.setScale(0.6f, 0.6f);
	m_infoText.setPosition(30.0f, 30.0f);
}

void ViewHandler::draw()
{
	if (m_infoClock.getElapsedTime().asSeconds() >= 0.5f)
	{
		m_fps = static_cast<int>(1.0f / m_fpsClock.getElapsedTime().asSeconds());
		m_infoClock.restart();
	}		
	
	m_infoText.setString("FPS: " + std::to_string(m_fps));
	m_window->draw(m_infoText);

	m_fpsClock.restart();
}
