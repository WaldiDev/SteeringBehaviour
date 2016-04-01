#include "Unit.h"
#include <SFML/Graphics/CircleShape.hpp>

Unit::Unit(Behaviours* behavior, sf::Sprite sprite, GameState::Enum state)
	: m_behaviour(behavior)
	, m_position(1280 / 2.f, 768 / 2.f)
	, m_rotation(0.0f)
	, m_maxVelocity(50.0f)
	, m_maxAcceleration(20.0f)
	, m_maxRotationVelocity(30.0f)
	, m_maxRotationAcceleration(10.0f)
	, m_rotationVelocity(0)
	, m_pathTime(0.0f)
	, m_fov(Pi / 4.f)
	, m_sprite(sprite)
	, m_orientation(0.0f)
	, m_state(state)
	, m_lastPathIndex(0)
	, m_pathOffset(1)
	, m_isPivot(false)
	, m_drawDebug(true)
	, m_offset(Vec2())
	, m_fixRotation(0.f)
{
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.f, m_sprite.getLocalBounds().height / 2.f);

	if (state == GameState::SCENARIO)
	{	
		;
		/*m_team.push_back(new Unit(behavior, sprite, GameState::TEAM, 0.f, Vec2(0.f, 0.f)));
		m_team.push_back(new Unit(behavior, sprite, GameState::TEAM, 10.0f, Vec2(0.f, 50.f)));
		m_team.push_back(new Unit(behavior, sprite, GameState::TEAM, 90.f, Vec2(-50.f, 50.f)));
		m_team.push_back(new Unit(behavior, sprite, GameState::TEAM, 160.0f, Vec2(-70.f, 30.f)));
		m_team.push_back(new Unit(behavior, sprite, GameState::TEAM, 200.f, Vec2(-70.f, 0.f)));
		m_team.push_back(new Unit(behavior, sprite, GameState::TEAM, 240.f, Vec2(-70.f, -30.f)));
		m_team.push_back(new Unit(behavior, sprite, GameState::TEAM, 270.f, Vec2(-50.f, -50.f)));
		m_team.push_back(new Unit(behavior, sprite, GameState::TEAM, 350.f, Vec2(0.f, -50.f)));*/
	}
}

void Unit::update(float delta, Target target)
{
	auto transform = m_behaviour->calculateTransform(m_state, target, *this);
	
	m_position += m_velocity * delta;
	m_orientation += m_rotationVelocity * delta;

	m_pathTime += delta;
	if (m_pathTime > 0.1f)
	{
		m_path.push_back(sf::Vertex(sf::Vector2f(m_position.x, m_position.y), sf::Color::Black));
		if (m_path.size() > 1000 - 1)
			m_path.erase(m_path.begin());
		m_pathTime = 0.0f;
	}

	m_velocity += transform.acceleration * delta;	
	if (m_velocity.lengthSqrt() > m_maxVelocity * m_maxVelocity)
		m_velocity = m_velocity.normalize() * m_maxVelocity;

	m_rotationVelocity += transform.angAcceleration * delta;
	if (m_rotationVelocity > m_maxRotationVelocity)
		m_rotationVelocity = m_maxRotationVelocity;

	for (auto& unit : m_team)
	{
		unit->update(delta, target);
	}

	for (auto& circle : m_angers)
	{
		circle.circle->setPosition(m_position.x + circle.offset.x, m_position.y + circle.offset.y);
	}
}

void Unit::draw(sf::RenderWindow& window)
{
	m_sprite.setPosition(m_position.x + m_offset.x, m_position.y + m_offset.y);
	if (m_fixRotation == 0.f)
		m_sprite.setRotation(m_orientation.asFloat()  * 180 / Pi);
	else
		m_sprite.setRotation(m_fixRotation);

	window.draw(m_sprite);
	window.draw(m_path.data(), m_path.size(), sf::Lines);

	for(auto& unit : m_team)
	{
		unit->draw(window);
	}

	for (auto& circle : m_angers)
	{
		window.draw(*circle.circle);
	}

	if (m_drawDebug)
	{
		sf::Vertex velocityLine[] =
		{
			sf::Vertex(sf::Vector2f(m_position.x, m_position.y), sf::Color::Red),
			sf::Vertex(sf::Vector2f(m_position.x + m_velocity.x, m_position.y + m_velocity.y), sf::Color::Red)
		};
		window.draw(velocityLine, 2, sf::Lines);		

		sf::Vertex targetLine[] =
		{
			sf::Vertex(sf::Vector2f(m_position.x, m_position.y), sf::Color::Blue),
			sf::Vertex(sf::Vector2f(m_lastTarget.position.x, m_lastTarget.position.y), sf::Color::Blue)
		};
		window.draw(targetLine, 2, sf::Lines);
	}
}

Target Unit::createTarget() const
{
	Target target;
	target.position = m_position;
	target.angVelocity = m_rotationVelocity;
	target.orientation = m_orientation;
	target.velocity = m_velocity;
	return target;
}


Vec2 Unit::getPosition() const
{
	return m_position;
}

Vec2 Unit::getVelocity() const
{
	return m_velocity;
}

Orientation Unit::getOrientation() const
{
	return m_orientation;
}

float Unit::getMaxAcceleration() const
{
	return m_maxAcceleration;
}

float Unit::getMaxVelocity() const
{
	return m_maxVelocity;
}

float Unit::getMaxRotationVelocity() const
{
	return m_maxRotationVelocity;
}

float Unit::getMaxRotationAcceleration() const
{
	return m_maxRotationAcceleration;
}

float Unit::getRotationVelocity() const
{
	return m_rotationVelocity;
}

void Unit::setRotationVelocity(float velocity)
{
	m_rotationVelocity = velocity;
}

void Unit::setVelocity(Vec2 velocity)
{
	m_velocity = velocity;
}

int Unit::getLastPathIndex() const
{
	return m_lastPathIndex;
}

void Unit::setLastPathIndex(int i)
{
	m_lastPathIndex = i;
}

int Unit::getPathOffset() const
{
	return m_pathOffset;
}

void Unit::setPathOffset(int i)
{
	m_pathOffset = i;
}

void Unit::setPosition(Vec2 position)
{
	m_position = position;
}

float Unit::getFov() const
{
	return m_fov;
}

void Unit::isPivot()
{
	m_isPivot = true;
}


void Unit::AddBehaviour(GameState::Enum beha, int prio)
{
	if (prio == 1)
		high.push_back(beha);

	else if (prio == 2)
		medium.push_back(beha);

	else
		low.push_back(beha);
}

void Unit::setTarget(Target target)
{
	m_lastTarget = target;
}

void Unit::setWander(Wander wander)
{
	m_wander = wander;
}

Anker Unit::createAnger(Vec2 position)
{
	sf::CircleShape* circle = new sf::CircleShape(5.f);
	circle->setOrigin(5.0f, 5.0f);
	circle->setFillColor(sf::Color::Cyan);

	Anker anker;
	anker.circle = circle;
	anker.offset = position;
	return anker;
}
