#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Unit.h"
#include "Vec2.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "Formation.h"

class SceneHandler
{
public:
	explicit SceneHandler(std::shared_ptr<sf::RenderWindow> window);
	void	update(float delta);
	void	draw();
	void	addUnit(Behaviours* behaviour, GameState::Enum state);
	void	clearUnits();
	void	togglePath();
	void	toogleObstacle();

	Vec2	getMousePos() const;
	void	setMousePos(Vec2 mousePos);
	std::vector<Vec2> getPathFollow() const;
	std::vector<Vec2> getEnemiePath(int i) const;
	std::vector<std::shared_ptr<Unit>> getUnits() const;
	std::vector<std::shared_ptr<Unit>> getTeam() const;
	std::vector<sf::RectangleShape>		getObstacle() const;
	std::vector<std::shared_ptr<Unit>>	m_team;
	std::vector<std::shared_ptr<Unit>>	m_enemies;
	std::vector<Anker>				m_ankers;
	void addWedge(Behaviours* behaviour, GameState::Enum state);
	Anker createAnger(Vec2 pos);

private:
	std::shared_ptr<sf::RenderWindow>	m_window;
	std::vector<std::shared_ptr<Unit>>	m_unitObjects;
	sf::Texture							m_unitTexture;
	Vec2								m_mousePos;
	bool								m_isPathActive;
	bool								m_isObstacleActive;
	std::vector<Vec2>					m_pathFollow = { Vec2(60.0f, 160.0f), Vec2(300.0f, 240.0f), Vec2(550.0f, 200.0f), Vec2(1110.0f, 100.0f), Vec2(980.0f, 340.0f), Vec2(960.0f, 600.0f),
														 Vec2(820.0f, 660.0f), Vec2(630.0f, 540.0f), Vec2(100.0f, 720.0f)};

	std::vector<Vec2>					m_enemiePath1 = { Vec2(150.0f, 50.0f), Vec2(300.0f, 50.0f), Vec2(300.0f, 250.0f), Vec2(150.0f, 250.0f) };
	std::vector<Vec2>					m_enemiePath2 = { Vec2(350.0f, 50.0f), Vec2(500.0f, 50.0f), Vec2(500.0f, 250.0f), Vec2(350.0f, 250.0f) };
	std::vector<Vec2>					m_enemiePath3 = { Vec2(550.0f, 50.0f), Vec2(700.0f, 50.0f), Vec2(700.0f, 250.0f), Vec2(550.0f, 250.0f) };
	std::vector<Vec2>					m_enemiePath4 = { Vec2(750.0f, 50.0f), Vec2(900.0f, 50.0f), Vec2(900.0f, 250.0f), Vec2(750.0f, 250.0f) };
	std::vector<Vec2>					m_enemiePath5 = { Vec2(950.0f, 50.0f), Vec2(1100.0f, 50.0f), Vec2(1100.0f, 250.0f), Vec2(950.0f, 250.0f) };
	std::vector<Vec2>					m_enemiePath6 = { Vec2(950.0f, 350.0f), Vec2(1200.0f, 350.0f), Vec2(1200.0f, 450.0f), Vec2(950.0f, 450.0f) };
	std::vector<Vec2>					m_enemiePath7 = { Vec2(550.0f, 550.0f), Vec2(700.0f, 550.0f), Vec2(700.0f, 750.0f), Vec2(550.0f, 750.0f) };
	std::vector<Vec2>					m_enemiePath8 = { Vec2(50.0f, 350.0f), Vec2(150.0f, 350.0f), Vec2(150.0f, 650.0f), Vec2(50.0f, 650.0f) };
	std::vector<sf::RectangleShape>		m_obstacles;
	Formation*							m_wedge;
	Unit*				m_leader;
};

