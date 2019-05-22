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
	std::vector<Boid> m_boids;
	bool m_mousePressedLast = false;
};

