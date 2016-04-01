#include "SceneHandler.h"
#include <SFML/Graphics/CircleShape.hpp>
#include "Formation.h"

SceneHandler::SceneHandler(std::shared_ptr<sf::RenderWindow> window)
	: m_window(window)
	, m_isPathActive(false)
	, m_isObstacleActive(false)
	, m_leader(nullptr)
{
	m_unitTexture.loadFromFile("unit.png");


	sf::RectangleShape shape1(sf::Vector2f(300.0f, 150.0f));
	shape1.setPosition(150.0f, 400.0f);
	shape1.setFillColor(sf::Color::Black);
	m_obstacles.push_back(shape1);

	/*sf::RectangleShape shape2(sf::Vector2f(120.0f, 200.0f));
	shape2.setPosition(500.0f, 70.0f);
	shape2.setFillColor(sf::Color::Black);
	m_obstacles.push_back(shape2);*/

	sf::RectangleShape shape3(sf::Vector2f(340.0f, 70.0f));
	shape3.setPosition(800.0f, 500.0f);
	shape3.setFillColor(sf::Color::Black);
	m_obstacles.push_back(shape3);

	m_ankers.push_back(createAnger(Vec2(-10.f, 30.0f)));
	m_ankers.push_back(createAnger(Vec2(0.f, 50.0f)));
	m_ankers.push_back(createAnger(Vec2(-50.f, 50.0f)));
	m_ankers.push_back(createAnger(Vec2(-70.f, 30.0f)));
	m_ankers.push_back(createAnger(Vec2(-70.f, 0.0f)));
	m_ankers.push_back(createAnger(Vec2(-70.f, -30.0f)));
	m_ankers.push_back(createAnger(Vec2(-50.f, -50.0f)));

}

void SceneHandler::update(float delta)
{
	Target target;
	target.position = m_mousePos;
	target.angVelocity = 0;
	target.orientation = 0;
	target.velocity = Vec2();

	for (auto unit : m_unitObjects)
	{
		unit->update(delta, target);
	}

	if (m_leader != nullptr)
	{
		m_leader->update(delta, target);
		auto pos = m_leader->getPosition();
		auto i = 0;
		for (auto unit : m_team)
		{			
			target.position = pos + m_ankers.at(i).offset;
			target.velocity = Vec2(20, 20);
			unit->update(delta, target);
			m_ankers.at(i).circle->setPosition(target.position.x, target.position.y);
			i++;
		}
	}
}

void SceneHandler::draw()
{
	if (m_isPathActive)
	{
		std::vector<sf::Vertex> vertex;
		for (auto point : m_pathFollow)
		{
			vertex.push_back(sf::Vertex(sf::Vector2f(point.x, point.y), sf::Color::Red));

			sf::CircleShape circle(10.0f);
			circle.setOrigin(10.0f, 10.0f);
			circle.setFillColor(sf::Color::Red);
			circle.setPosition(point.x, point.y);
			m_window->draw(circle);
			
		}
		vertex.push_back(vertex.at(0));
		m_window->draw(vertex.data(), vertex.size(), sf::LinesStrip);

		vertex.clear();
		for (auto point : m_enemiePath1)
		{
			vertex.push_back(sf::Vertex(sf::Vector2f(point.x, point.y), sf::Color::Black));

			sf::CircleShape circle(5.0f);
			circle.setOrigin(5.0f, 5.0f);
			circle.setFillColor(sf::Color::Red);
			circle.setPosition(point.x, point.y);
			m_window->draw(circle);

		}
		vertex.push_back(vertex.at(0));
		m_window->draw(vertex.data(), vertex.size(), sf::LinesStrip);

		vertex.clear();
		for (auto point : m_enemiePath2)
		{
			vertex.push_back(sf::Vertex(sf::Vector2f(point.x, point.y), sf::Color::Red));

			sf::CircleShape circle(5.0f);
			circle.setOrigin(5.0f, 5.0f);
			circle.setFillColor(sf::Color::Red);
			circle.setPosition(point.x, point.y);
			m_window->draw(circle);

		}
		vertex.push_back(vertex.at(0));
		m_window->draw(vertex.data(), vertex.size(), sf::LinesStrip);

		vertex.clear();
		for (auto point : m_enemiePath3)
		{
			vertex.push_back(sf::Vertex(sf::Vector2f(point.x, point.y), sf::Color::Red));

			sf::CircleShape circle(5.0f);
			circle.setOrigin(5.0f, 5.0f);
			circle.setFillColor(sf::Color::Red);
			circle.setPosition(point.x, point.y);
			m_window->draw(circle);

		}
		vertex.push_back(vertex.at(0));
		m_window->draw(vertex.data(), vertex.size(), sf::LinesStrip);

		vertex.clear();
		for (auto point : m_enemiePath4)
		{
			vertex.push_back(sf::Vertex(sf::Vector2f(point.x, point.y), sf::Color::Red));

			sf::CircleShape circle(5.0f);
			circle.setOrigin(5.0f, 5.0f);
			circle.setFillColor(sf::Color::Red);
			circle.setPosition(point.x, point.y);
			m_window->draw(circle);

		}
		vertex.push_back(vertex.at(0));
		m_window->draw(vertex.data(), vertex.size(), sf::LinesStrip);

		vertex.clear();
		for (auto point : m_enemiePath5)
		{
			vertex.push_back(sf::Vertex(sf::Vector2f(point.x, point.y), sf::Color::Red));

			sf::CircleShape circle(5.0f);
			circle.setOrigin(5.0f, 5.0f);
			circle.setFillColor(sf::Color::Red);
			circle.setPosition(point.x, point.y);
			m_window->draw(circle);

		}
		vertex.push_back(vertex.at(0));
		m_window->draw(vertex.data(), vertex.size(), sf::LinesStrip);

		vertex.clear();
		for (auto point : m_enemiePath6)
		{
			vertex.push_back(sf::Vertex(sf::Vector2f(point.x, point.y), sf::Color::Red));

			sf::CircleShape circle(5.0f);
			circle.setOrigin(5.0f, 5.0f);
			circle.setFillColor(sf::Color::Red);
			circle.setPosition(point.x, point.y);
			m_window->draw(circle);

		}
		vertex.push_back(vertex.at(0));
		m_window->draw(vertex.data(), vertex.size(), sf::LinesStrip);

		vertex.clear();
		for (auto point : m_enemiePath7)
		{
			vertex.push_back(sf::Vertex(sf::Vector2f(point.x, point.y), sf::Color::Red));

			sf::CircleShape circle(5.0f);
			circle.setOrigin(5.0f, 5.0f);
			circle.setFillColor(sf::Color::Red);
			circle.setPosition(point.x, point.y);
			m_window->draw(circle);

		}
		vertex.push_back(vertex.at(0));
		m_window->draw(vertex.data(), vertex.size(), sf::LinesStrip);

		vertex.clear();
		for (auto point : m_enemiePath8)
		{
			vertex.push_back(sf::Vertex(sf::Vector2f(point.x, point.y), sf::Color::Red));

			sf::CircleShape circle(5.0f);
			circle.setOrigin(5.0f, 5.0f);
			circle.setFillColor(sf::Color::Red);
			circle.setPosition(point.x, point.y);
			m_window->draw(circle);

		}
		vertex.push_back(vertex.at(0));
		m_window->draw(vertex.data(), vertex.size(), sf::LinesStrip);
	}		

	if (m_isObstacleActive)
	{
		for (auto shape : m_obstacles)
		{
			m_window->draw(shape);
		}		
	}

	for (auto unit : m_unitObjects)
	{
		unit->draw(*m_window);
	}

	if (m_leader != nullptr)
	{
		for (auto& circle : m_ankers)
		{
			m_window->draw(*circle.circle);
		}

		m_leader->draw(*m_window);

		for (auto unit : m_team)
		{
			unit->draw(*m_window);
		}
	}
}

void SceneHandler::addUnit(Behaviours* behaviour, GameState::Enum state)
{
	if (state != GameState::SCENARIO)
	{
		std::shared_ptr<Unit> unit(new Unit(behaviour, sf::Sprite(m_unitTexture, sf::IntRect(0, 0, 32, 32)), state));
		m_unitObjects.push_back(unit);
	}
	else
	{
		m_leader = new Unit(behaviour, sf::Sprite(m_unitTexture, sf::IntRect(0, 0, 32, 32)), state);
		
		std::shared_ptr<Unit> unit1(new Unit(behaviour, sf::Sprite(m_unitTexture, sf::IntRect(0, 0, 32, 32)), GameState::TEAM));
		unit1->m_fixRotation = 30;
		m_team.push_back(unit1);
		std::shared_ptr<Unit> unit2(new Unit(behaviour, sf::Sprite(m_unitTexture, sf::IntRect(0, 0, 32, 32)), GameState::TEAM));
		unit2->m_fixRotation = 60;
		m_team.push_back(unit2);
		std::shared_ptr<Unit> unit3(new Unit(behaviour, sf::Sprite(m_unitTexture, sf::IntRect(0, 0, 32, 32)), GameState::TEAM));
		unit3->m_fixRotation = 90;
		m_team.push_back(unit3);
		std::shared_ptr<Unit> unit4(new Unit(behaviour, sf::Sprite(m_unitTexture, sf::IntRect(0, 0, 32, 32)), GameState::TEAM));
		unit4->m_fixRotation = 120;
		m_team.push_back(unit4);
		std::shared_ptr<Unit> unit5(new Unit(behaviour, sf::Sprite(m_unitTexture, sf::IntRect(0, 0, 32, 32)), GameState::TEAM));
		unit5->m_fixRotation = 150;
		m_team.push_back(unit5);
		std::shared_ptr<Unit> unit6(new Unit(behaviour, sf::Sprite(m_unitTexture, sf::IntRect(0, 0, 32, 32)), GameState::TEAM));
		unit6->m_fixRotation = 180;
		m_team.push_back(unit6);
		std::shared_ptr<Unit> unit7(new Unit(behaviour, sf::Sprite(m_unitTexture, sf::IntRect(0, 0, 32, 32)), GameState::TEAM));
		unit7->m_fixRotation = 210;
		m_team.push_back(unit7);

		std::shared_ptr<Unit> enemie1(new Unit(behaviour, sf::Sprite(m_unitTexture, sf::IntRect(0, 0, 32, 32)), GameState::ENEMIE1));
		m_unitObjects.push_back(enemie1);
		std::shared_ptr<Unit> enemie2(new Unit(behaviour, sf::Sprite(m_unitTexture, sf::IntRect(0, 0, 32, 32)), GameState::ENEMIE2));
		m_unitObjects.push_back(enemie2);
		std::shared_ptr<Unit> enemie3(new Unit(behaviour, sf::Sprite(m_unitTexture, sf::IntRect(0, 0, 32, 32)), GameState::ENEMIE3));
		m_unitObjects.push_back(enemie3);
		std::shared_ptr<Unit> enemie4(new Unit(behaviour, sf::Sprite(m_unitTexture, sf::IntRect(0, 0, 32, 32)), GameState::ENEMIE4));
		m_unitObjects.push_back(enemie4);
		std::shared_ptr<Unit> enemie5(new Unit(behaviour, sf::Sprite(m_unitTexture, sf::IntRect(0, 0, 32, 32)), GameState::ENEMIE5));
		m_unitObjects.push_back(enemie5);
		std::shared_ptr<Unit> enemie6(new Unit(behaviour, sf::Sprite(m_unitTexture, sf::IntRect(0, 0, 32, 32)), GameState::ENEMIE6));
		m_unitObjects.push_back(enemie6);
		std::shared_ptr<Unit> enemie7(new Unit(behaviour, sf::Sprite(m_unitTexture, sf::IntRect(0, 0, 32, 32)), GameState::ENEMIE7));
		m_unitObjects.push_back(enemie7);
		std::shared_ptr<Unit> enemie8(new Unit(behaviour, sf::Sprite(m_unitTexture, sf::IntRect(0, 0, 32, 32)), GameState::ENEMIE8));
		m_unitObjects.push_back(enemie8);
	}
}

void SceneHandler::clearUnits()
{
	m_unitObjects.clear();
}

void SceneHandler::togglePath()
{
	if (m_isPathActive)
		m_isPathActive = false;
	else
		m_isPathActive = true;
}

void SceneHandler::toogleObstacle()
{
	if (m_isObstacleActive)
		m_isObstacleActive = false;
	else
		m_isObstacleActive = true;
}

Vec2 SceneHandler::getMousePos() const
{
	return m_mousePos;
}

void SceneHandler::setMousePos(Vec2 mousePos)
{
	m_mousePos = mousePos;
}

std::vector<Vec2> SceneHandler::getPathFollow() const
{
	return m_pathFollow;
}

std::vector<std::shared_ptr<Unit>> SceneHandler::getUnits() const
{
	return m_unitObjects;
}

std::vector<std::shared_ptr<Unit>> SceneHandler::getTeam() const
{
	return m_team;
}


std::vector<sf::RectangleShape> SceneHandler::getObstacle() const
{
	return m_obstacles;
}


void SceneHandler::addWedge(Behaviours* behaviour, GameState::Enum state)
{
	
	m_wedge->addPivot(new Unit(behaviour, sf::Sprite(m_unitTexture, sf::IntRect(0, 0, 32, 32)), state));
	m_wedge->m_pivot->isPivot();
	for (auto i = 0; i < 8; ++i)
	{
		
	}
}

Anker SceneHandler::createAnger(Vec2 position)
{
	sf::CircleShape* circle = new sf::CircleShape(5.f);
	circle->setOrigin(5.0f, 5.0f);
	circle->setFillColor(sf::Color::Cyan);

	Anker anker;
	anker.circle = circle;
	anker.offset = position;
	return anker;
}

std::vector<Vec2> SceneHandler::getEnemiePath(int i) const
{
	if (i == 1)
	{
		return m_enemiePath1;
	}
	if (i == 2)
	{
		return m_enemiePath2;
	}
	if (i == 3)
	{
		return m_enemiePath3;
	}
	if (i == 4)
	{
		return m_enemiePath4;
	}
	if (i == 5)
	{
		return m_enemiePath5;
	}
	if (i == 6)
	{
		return m_enemiePath6;
	}
	if (i == 7)
	{
		return m_enemiePath7;
	}
	if (i == 8)
	{
		return m_enemiePath8;
	}
}
