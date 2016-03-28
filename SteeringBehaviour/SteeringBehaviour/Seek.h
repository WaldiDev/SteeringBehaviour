#pragma once
#include "IBehaviour.h"

class SceneHandler;
class Unit;

class Seek : public IBehaviour
{
public:
	explicit Seek(SceneHandler* sceneHandler);
	sf::Vector2f	use(Unit* unit) override;

private:
	SceneHandler*	m_sceneHandler;
};

