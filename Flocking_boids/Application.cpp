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
		direction += this->getCohesion(boid);
		boid.update(direction);
		if (boid.getPos().x > window.getSize().x) {
			boid.setPosition({ 0, boid.getPos().y });
		}
		else if (boid.getPos().x < 0) {
			boid.setPosition({ (float)window.getSize().x, boid.getPos().y });
		}
		if (boid.getPos().y > window.getSize().y) {
			boid.setPosition({boid.getPos().x, 0 });
		}
		else if (boid.getPos().y < 0) {
			boid.setPosition({ boid.getPos().x, (float)window.getSize().y });
		}
	}
}

void Application::render(sf::RenderWindow& window) {
	for (auto& boid : m_boids) {
		boid.render(window);
	}
}

const Vec2& Application::getAllignment(const Boid& boid) const {
	Vec2 vec(0,0);
	int neighborCount = 0;
	for (auto& other : m_boids) {
		if (boid.getPos() != other.getPos()) {
			if (boid.getDistance(other) < m_visionRange) {
				vec += other.getDirection();
				neighborCount++;
			}
		}
	}
	if (neighborCount == 0) {
		return vec;
	}
	vec /= neighborCount;
	vec.normalize();
	return vec;
}

const Vec2& Application::getCohesion(const Boid& boid) const {
	Vec2 vec(0, 0);
	int neighborCount = 0;
	for (auto& other : m_boids) {
		if (boid.getPos() != other.getPos()) {
			if (boid.getDistance(other) < m_visionRange) {
				vec += other.getPos();
				neighborCount++;
			}
		}
		if (neighborCount == 0) {
			return vec;
		}
		vec /= neighborCount;
		vec -= boid.getPos();
		vec.normalize();
		return vec;
	}
}