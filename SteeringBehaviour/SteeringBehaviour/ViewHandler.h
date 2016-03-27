#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class ViewHandler
{
public:
	explicit	ViewHandler(std::shared_ptr<sf::RenderWindow> window);
	void		draw();

	
private:
	std::shared_ptr<sf::RenderWindow>	m_window;
	sf::Font							m_font;
	sf::Clock							m_fpsClock;
	sf::Clock							m_infoClock;
	sf::Text							m_infoText;
	int									m_fps;
};

