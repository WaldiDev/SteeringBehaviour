#pragma once
#include "Helper.h"

class SceneHandler;
class Unit;

class Behaviours
{
public:
	explicit Behaviours(SceneHandler* scene);

	Transform	calculateTransform(GameState::Enum state, Target target, Unit& unit);

private:
	Transform	align(Vec2 target, Unit& unit) const;
	Transform	seek(Target target, Unit& unit) const;
	Transform	flee(Target target, Unit& unit) const;
	Transform	arrive(Target target, Unit& unit) const;
	Transform	wander(Unit& unit);
	Transform	pursuit(Target target, Unit& unit) const;
	Transform	evade(Target target, Unit& unit) const;
	Transform	pathFollow(Unit& unit, std::vector<Vec2> path) const;
	Transform	collisionFov(Target target, Unit& unit);
	Transform	collisionPrediction(Target target, Unit& unit);
	Transform	obstacleAvoidance(Target target, Unit& unit);
	Transform	seperation(Unit& unit);
	Transform	scenario(Target target, Unit& unit);
	Transform	team(Target target, Unit& unit);
	Transform	velocityMatching(Target target, Unit& unit);
	
	float		look(Vec2 target, Unit& unit) const;

private:
	float		randomBinomial() const;
	float		randFloat() const;
	float		mapToRange(float rotation) const;
	Vec2		rayBoxIntersection(Vec2 point1, Vec2 point2, Vec2 start, Vec2 ray);
	Vec2		getCollisionNormals(Vec2 collision, Vec2 point1, Vec2 point2);

private:
	SceneHandler*	m_scene;

	Wander			m_wander;
	const float		m_Epsilon = 0.00001f;
	const float		m_Pi = 3.1415927410125732421875f;
	const float		m_AlignProximityAngel = 45.0f * m_Pi / 180;
	const float		m_AlignSatisfactionAngel = 3.0f * m_Pi / 180;
	const float		m_ArriveRadius = 1.0f;
	const float		m_ArriveFullSpeedRadius = 50.0f;
	const float		m_TimeToTarget = 10.0f;
	
	const float		m_PersuitPredictionTime = 5.5f;
	const float		m_SeperationRadius = 30.0f;
	const float		m_viewDistance = 40.0f;

	
};

