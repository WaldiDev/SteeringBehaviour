#include "Unit.h"

Unit::Unit(std::shared_ptr<IBehaviour> behavior, sf::Sprite sprite)
	: m_behaviour(behavior)
	, m_orientation(0.0f)
	, m_rotation(0.0f)
	, m_maxVelocity(100.0f)
	, m_maxAcceleration(20.0f)
	, m_sprite(sprite)
{
}

Unit::~Unit()
{
}

void Unit::init()
{

}

void Unit::update(float delta)
{
	m_position += m_velocity * delta;
	m_orientation += m_rotation * delta;

	auto acceleration = m_behaviour->use(this);
	m_velocity += acceleration * delta;

	auto m_velocityLength = sqrtf(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
	if (m_velocityLength > m_maxVelocity)
	{
		m_velocity /= m_velocityLength;
		m_velocity *= m_maxVelocity;
	}
}

void Unit::draw(sf::RenderWindow& window)
{
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation);
	window.draw(m_sprite);
}

void Unit::setBehaviour(std::shared_ptr<IBehaviour> behavior)
{
}

sf::Vector2f Unit::getPosition() const
{
	return m_position;
}

float Unit::getMaxAcceleration() const
{
	return m_maxAcceleration;
}
