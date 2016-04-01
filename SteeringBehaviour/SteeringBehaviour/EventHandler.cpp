#include "EventHandler.h"
EventHandler::EventHandler(std::shared_ptr<sf::RenderWindow> window, SceneHandler* sceneHandler, ViewHandler* viewHandler, Behaviours* behaviours)
	: m_window(window)
	, m_sceneHandler(sceneHandler)
	, m_viewHandler(viewHandler)
	, m_behaviours(behaviours)
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
		case sf::Event::MouseMoved: 
			onMouseMoved(event.mouseMove.x, event.mouseMove.y);
			break;
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
		m_sceneHandler->addUnit(m_behaviours, GameState::SEEK);
		m_viewHandler->setDemoName("Seek");
	}
	else if (key == sf::Keyboard::Num2)
	{
		m_sceneHandler->addUnit(m_behaviours, GameState::FLEE);
		m_viewHandler->setDemoName("Flee");
	}
	else if (key == sf::Keyboard::Num3)
	{
		m_sceneHandler->addUnit(m_behaviours, GameState::ARRIVE);
		m_viewHandler->setDemoName("Arrive");
	}
	else if (key == sf::Keyboard::Num4)
	{
		m_sceneHandler->addUnit(m_behaviours, GameState::WANDER);
		m_viewHandler->setDemoName("Wander");
	}
	else if (key == sf::Keyboard::Num5)
	{
		m_sceneHandler->addUnit(m_behaviours, GameState::PURSUIT);
		m_viewHandler->setDemoName("Pursuit");
	}
	else if (key == sf::Keyboard::Num6)
	{
		m_sceneHandler->addUnit(m_behaviours, GameState::EVADE);
		m_viewHandler->setDemoName("Evade");
	}
	else if (key == sf::Keyboard::Num7)
	{
		m_sceneHandler->addUnit(m_behaviours, GameState::PATHFOLLOW);
		m_viewHandler->setDemoName("PathFollow");
	}
	else if (key == sf::Keyboard::Num8)
	{
		m_sceneHandler->addUnit(m_behaviours, GameState::COLLISIONFOV);
		m_viewHandler->setDemoName("Collision FOV");
	}
	else if (key == sf::Keyboard::Num9)
	{
		m_sceneHandler->addUnit(m_behaviours, GameState::COLLISIONPREDICTION);
		m_viewHandler->setDemoName("Collision Prediction");
	}
	else if (key == sf::Keyboard::Num0)
	{
		m_sceneHandler->addUnit(m_behaviours, GameState::OBSTACLEAVOIDANCE);
		m_viewHandler->setDemoName("Obstacle Avoidance");
	}
	else if (key == sf::Keyboard::S)
	{
		m_sceneHandler->addUnit(m_behaviours, GameState::SCENARIO);
		m_viewHandler->setDemoName("Scenario");
	}
	else if (key == sf::Keyboard::P)
	{
		m_sceneHandler->togglePath();
	}
	else if (key == sf::Keyboard::O)
	{
		m_sceneHandler->toogleObstacle();
	}
	else if (key == sf::Keyboard::C)
	{
		m_sceneHandler->clearUnits();
		m_viewHandler->setDemoName("Nothing");
	}
}

void EventHandler::onMouseMoved(int mouseX, int mouseY)
{
	m_sceneHandler->setMousePos(Vec2((float)mouseX, (float)mouseY));
}
