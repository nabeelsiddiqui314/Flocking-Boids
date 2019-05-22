#include "stdafx.h"
#include "Application.h"


Application::Application()
: m_visionRange(20) {
	srand(time(NULL));
}

void Application::update(const sf::RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_mousePressedLast) {
		Boid b( {(float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y },
			    { (float)(rand() % 10) - 5.0f, (float)(rand() % 10) - 5.0f });
		m_boids.push_back(b);
	}
	m_mousePressedLast = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	for (auto& boid : m_boids) {
		Vec2 direction(0,0);
		direction += this->getAllignment(boid);
		boid.update(direction);
	}
}

void Application::render(sf::RenderWindow& window) {
	for (auto& boid : m_boids) {
		boid.render(window);
	}
}

const Vec2& Application::getAllignment(const Boid& boid) const {
	Vec2 sum(0,0);
	int neighborCount = 0;
	for (auto& other : m_boids) {
		if (boid.getPos() != other.getPos()) {
			if (boid.getDistance(other) < m_visionRange) {
				sum += other.getDirection();
				neighborCount++;
			}
		}
	}
	if (neighborCount == 0) {
		return sum;
	}
	sum /= neighborCount;
	sum.normalize();
	return sum;
}