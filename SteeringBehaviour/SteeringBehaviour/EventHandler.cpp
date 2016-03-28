#include "EventHandler.h"
#include "Seek.h"

EventHandler::EventHandler(std::shared_ptr<sf::RenderWindow> window, SceneHandler& sceneHandler)
	: m_window(window)
	, m_sceneHandler(sceneHandler)
{
}

void EventHandler::update()
{
	sf::Event event;
	while(m_window->pollEvent(event))
	{
		switch(event.type)
		{
		case sf::Event::Closed: 
			m_window->close();
			break;		
		case sf::Event::KeyPressed: 
			onKeyPressed(event.key.code);
			break;

		case sf::Event::Resized: break;
		case sf::Event::LostFocus: break;
		case sf::Event::GainedFocus: break;
		case sf::Event::TextEntered: break;
		case sf::Event::KeyReleased: break;
		case sf::Event::MouseWheelMoved: break;
		case sf::Event::MouseWheelScrolled: break;
		case sf::Event::MouseButtonPressed: break;
		case sf::Event::MouseButtonReleased: break;
		case sf::Event::MouseMoved: break;
		case sf::Event::MouseEntered: break;
		case sf::Event::MouseLeft: break;
		case sf::Event::JoystickButtonPressed: break;
		case sf::Event::JoystickButtonReleased: break;
		case sf::Event::JoystickMoved: break;
		case sf::Event::JoystickConnected: break;
		case sf::Event::JoystickDisconnected: break;
		case sf::Event::TouchBegan: break;
		case sf::Event::TouchMoved: break;
		case sf::Event::TouchEnded: break;
		case sf::Event::SensorChanged: break;
		case sf::Event::Count: break;
		default: break;
		}
	}
}

void EventHandler::onKeyPressed(int key)
{
	if (key == sf::Keyboard::Num1)
	{
		m_sceneHandler.addUnit(std::make_shared<Seek>());
	}
}
