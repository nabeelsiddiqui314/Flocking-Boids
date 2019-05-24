#pragma once
#include "Boid.h"

class Application
{
public:
	Application();
public:
	void update(const sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
private:
	const Vec2& getAllignment(const Boid& boid) const;
	const Vec2& getCohesion(const Boid& boid) const;
	const Vec2& getCrowdSeperation(const Boid& boid) const;
	const Vec2& getPredatorAvoidance(const Boid& boid) const;
private:
	std::vector<Boid> m_boids;
	bool m_LmousePressedLast = false;
	bool m_RmousePressedLast = false;
	const int m_visionRange;
	const int m_predatorVisionRange;
};

