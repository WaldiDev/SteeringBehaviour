#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Behaviours.h"
#include "Helper.h"
#include <SFML/Graphics/CircleShape.hpp>

class Unit
{
public:
	explicit Unit(Behaviours* behavior, sf::Sprite sprite, GameState::Enum state);

	void	update(float delta, Target target);
	void	draw(sf::RenderWindow& window);

	float		getMaxAcceleration() const;
	float		getMaxVelocity() const;
	float		getMaxRotationVelocity() const;
	float		getMaxRotationAcceleration() const;
	float		getRotationVelocity() const;
	Vec2		getPosition() const;
	Vec2		getVelocity() const;
	Orientation getOrientation() const;
	int			getLastPathIndex() const;
	int			getPathOffset() const;
	float		getFov() const;
	Target		createTarget() const;
	
	void	setRotationVelocity(float velocity);
	void	setVelocity(Vec2 velocity);
	void	setLastPathIndex(int i);
	void	setPathOffset(int i);
	
	void	setPosition(Vec2 position);
	void	isPivot();
	void	AddBehaviour(GameState::Enum beha, int prio);
	int						m_collided = std::numeric_limits<int>::infinity();
	void	setTarget(Target target);
	void	setWander(Wander wander);
	Anker createAnger(Vec2 position);
	float				m_fixRotation;

private:
	Wander					m_wander;
	Behaviours*				m_behaviour;
	Vec2					m_position;
	Vec2					m_velocity;
	float					m_rotation;
	float					m_maxVelocity;
	float					m_maxAcceleration;
	float					m_maxRotationVelocity;
	float					m_maxRotationAcceleration;
	float					m_rotationVelocity;
	float					m_pathTime;
	float					m_fov;
	sf::Sprite				m_sprite;
	Orientation				m_orientation;
	GameState::Enum			m_state;
	std::vector<sf::Vertex>	m_path;
	int						m_lastPathIndex;
	int						m_pathOffset;
	bool					m_isPivot;
	std::vector<Unit*>		m_team;
	std::vector <GameState::Enum>	high;
	std::vector<GameState::Enum>	medium;
	std::vector<GameState::Enum>	low;
	bool					m_drawDebug;
	Target					m_lastTarget;
	Vec2					m_offset;
	
	std::vector<Anker> m_angers;
	
};

