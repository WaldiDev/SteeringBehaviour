#pragma once
#include <SFML/System/Vector2.hpp>

class IBehaviour
{
public:
	virtual sf::Vector2f use() = 0;
	virtual ~IBehaviour() {}
};
