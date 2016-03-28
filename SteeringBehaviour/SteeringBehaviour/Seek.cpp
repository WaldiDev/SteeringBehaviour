#include "Seek.h"
#include "SceneHandler.h"

Seek::Seek(SceneHandler* sceneHandler)
	: m_sceneHandler(sceneHandler)
{
}

sf::Vector2f Seek::use(Unit* unit)
{
	auto target = m_sceneHandler->getMousePos();
	auto position = unit->getPosition();
	
	// Normalize
	auto velocity = target - position;
	auto velocityLength = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y);
	if (velocityLength > std::numeric_limits<float>::epsilon())
	{
		velocity /= velocityLength;
	}

	return velocity * unit->getMaxAcceleration();
}
