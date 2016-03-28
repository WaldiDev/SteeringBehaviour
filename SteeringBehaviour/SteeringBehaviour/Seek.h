#pragma once
#include "IBehaviour.h"

class Seek : public IBehaviour
{
public:
	sf::Vector2f	use() override;
};

