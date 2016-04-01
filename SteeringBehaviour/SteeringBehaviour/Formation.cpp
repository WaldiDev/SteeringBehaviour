#include "Formation.h"


Formation::Formation()
	: m_formationWidth(20.f)
	, m_pivot(nullptr)
{
	m_targets[0].position = Vec2(0, 1 * m_formationWidth);
	m_targets[0].orientation = 0;

	m_targets[1].position = Vec2(1 * m_formationWidth, 0);
	m_targets[1].orientation = -Pi / 4;

	m_targets[2].position = Vec2(-1 * m_formationWidth, 0);
	m_targets[2].orientation = Pi / 4;

	m_targets[3].position = Vec2(2 * m_formationWidth, -1 * m_formationWidth);
	m_targets[3].orientation = Pi;

	m_targets[4].position = Vec2(0, 2 * m_formationWidth);
	m_targets[4].orientation = 0;

	m_targets[5].position = Vec2(2 * m_formationWidth, 0);
	m_targets[5].orientation = -Pi / 4;

	m_targets[6].position = Vec2(-2 * m_formationWidth, 0);
	m_targets[6].orientation = Pi / 4;

	m_targets[7].position = Vec2(2 * m_formationWidth, -2 * m_formationWidth);
	m_targets[7].orientation = Pi;

}

Formation::~Formation()
{
}

void Formation::addPivot(Unit* pivot)
{
	m_pivot = pivot;
}

Target Formation::GetTargetSlot(int i)
{
	Target temp;
	temp.orientation = m_pivot->getOrientation().asFloat() + m_targets[i].orientation.asFloat();
	temp.position = RotateSlots(m_targets[i]);
	return temp;
}

Vec2 Formation::RotateSlots(Target slot)
{
	Vec2 pos = m_pivot->getPosition() + slot.position;
	float angle = m_pivot->getOrientation().asFloat() - pos.getAngle();

	float fX = cosf(angle) * (slot.position.x) - sinf(angle) * (slot.position.y) + m_pivot->getPosition().x;
	float fY = sinf(angle) * (slot.position.x) + cosf(angle) * (slot.position.y) + m_pivot->getPosition().y;
	return Vec2(fX, fY);
}

void Formation::draw(sf::RenderWindow& window)
{
	
}

void Formation::update(float delta, Target target)
{
	
}

