#pragma once
#include "Vec2.h"
#include <math.h>
#include <SFML/Graphics/CircleShape.hpp>

const float	Pi = 3.1415927410125732421875f;

struct GameState
{
	enum Enum
	{
		SEEK,
		FLEE,
		ARRIVE,
		WANDER,
		PURSUIT,
		EVADE,
		PATHFOLLOW,
		COLLISIONFOV,
		COLLISIONPREDICTION,
		OBSTACLEAVOIDANCE,
		SCENARIO,
		TEAM,
		ENEMIE1,
		ENEMIE2,
		ENEMIE3,
		ENEMIE4,
		ENEMIE5,
		ENEMIE6,
		ENEMIE7,
		ENEMIE8
	};

	static const char* toString(Enum gameState)
	{
		switch (gameState)
		{
		case SEEK: 
			return "SEEK";
		case FLEE: 
			return "FLEE";
		case ARRIVE: 
			return "ARRIVE";
		case WANDER:
			return "WANDER";			
		case PURSUIT: 
			return "PURSUIT";
		case EVADE:
			return "EVADE";
		case PATHFOLLOW:
			return "PATHFOLLOW";
		case COLLISIONFOV:
			return "COLLISIONFOV";
		case COLLISIONPREDICTION:
			return "COLLISIONPREDICTION";
		case OBSTACLEAVOIDANCE:
			return	"OBSTACLEAVOIDANCE";
		case SCENARIO:
			return "SCENARIO";
		default: 
			return "UNKNOWN";
		}
	}
};

struct Wander
{
	float			orientation = 1.0f;
	const float		rate = 5.0f;
	const float		offset = 10.0f;
	const float		radius = 20.0f;

	void operator=(const Wander rhs) { orientation = rhs.orientation; }
};

struct Anker
{
	sf::CircleShape* circle;
	Vec2 offset;
};

struct Transform
{
	Vec2	acceleration;
	float	angAcceleration;
	
	Transform operator* (const float &rhs) const
	{
		Transform temp;
		temp.acceleration.x = acceleration.x * rhs;
		temp.acceleration.y = acceleration.y * rhs;
		return temp;
	}
};

struct Orientation
{
public:
	Orientation(): m_angle(0) {}
	explicit Orientation(float angle) : m_angle(angle) { }
	
	float	asFloat() const { return m_angle; }
	Vec2	asVec2() const
	{
		Vec2 temp;
		temp.x = cosf(m_angle);
		temp.y = sinf(m_angle);
		return temp;
	}

	void		operator=(const float rhs) { m_angle = rhs; }
	void		operator+=(const float rhs) { m_angle += rhs; }
	Orientation	operator+(const float rhs) 
	{ 
		m_angle += rhs; 
		return *this; 
	}

private:
	float m_angle;
};

struct Target
{
	Vec2		position;
	Vec2		velocity;
	Orientation	orientation;
	float		angVelocity;
};
