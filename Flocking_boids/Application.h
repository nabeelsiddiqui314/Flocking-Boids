#pragma once
#include "Boid.h"
#include "Wall.h"

class Application
{
public:
	Application();
public:
	void update(const sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
private:
	const Vec2 getAllignment(const Boid& boid) const;
	const Vec2 getCohesion(const Boid& boid) const;
	const Vec2 getCrowdSeperation(const Boid& boid) const;
	const Vec2 getPredatorAvoidance(const Boid& boid) const;
	const Vec2 getWallAvoidance(const Boid& boid) const;
private:
	std::vector<Boid> m_boids;
	std::vector<Wall> m_walls;
	bool m_LmousePressedLast = false;
	bool m_RmousePressedLast = false;
	bool m_spacePressedLast = false;
	const int m_visionRange;
	const int m_predatorVisionRange;
	const int m_wallAvoidDist;
};

