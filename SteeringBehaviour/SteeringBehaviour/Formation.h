#pragma once
#include "Helper.h"
#include <vector>
#include "Unit.h"

class Formation
{
public:
	Formation();
	~Formation();

	void addPivot(Unit* pivot);
	
	Target GetTargetSlot(int i);
	Vec2 RotateSlots(Target slot);
	void	update(float delta, Target target);
	void	draw(sf::RenderWindow& window);

	Unit* m_pivot;
	Target m_targets[8];
	//Unit m_units[8];
	float m_formationWidth;
};

