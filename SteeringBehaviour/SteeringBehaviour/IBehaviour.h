#pragma once
#include <SFML/System/Vector2.hpp>

class Unit;

class IBehaviour
{
public:
	virtual sf::Vector2f use(Unit* unit) = 0;
	virtual ~IBehaviour() {}
};
