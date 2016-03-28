#include "Unit.h"

Unit::Unit(std::shared_ptr<IBehaviour> behavior, sf::Sprite sprite)
	: m_behaviour(behavior)
	, m_maxVelocity(100.0f)
	, m_sprite(sprite)
{
}

Unit::~Unit()
{
}

void Unit::init()
{

}
