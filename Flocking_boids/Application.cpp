#include "stdafx.h"
#include "Application.h"


Application::Application()
: m_visionRange(100) {
	srand(time(NULL));
}

void Application::update(const sf::RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_mousePressedLast) {
		Boid b( {(float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y },
			{ (float)(rand() % 10) - 5.0f, (float)(rand() % 10) - 5.0f }, { sf::Uint8(rand() % 255), sf::Uint8(rand() % 255), sf::Uint8(rand() % 255) });
		m_boids.push_back(b);
	}
	m_mousePressedLast = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	for (auto& boid : m_boids) {
		Vec2 direction(0,0);
		//direction.x += (float)(rand() % 3 - 1) / 10;
		//direction.y += (float)(rand() % 3 - 1) / 10;
		direction += this->getAllignment(boid);
		direction += this->getCohesion(boid);
		direction += this->getCrowdSeperation(boid);
		boid.setColor(getAverageColor(boid));
		boid.update(direction);
		if (boid.getPos().x > window.getSize().x) {
			boid.setPos({ 0, boid.getPos().y });
		}
		else if (boid.getPos().x < 0) {
			boid.setPos({ (float)window.getSize().x, boid.getPos().y });
		}
		if (boid.getPos().y > window.getSize().y) {
			boid.setPos({boid.getPos().x, 0 });
		}
		else if (boid.getPos().y < 0) {
			boid.setPos({ boid.getPos().x, (float)window.getSize().y });
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
	}
	if (neighborCount == 0) {
		return vec;
	}
	vec /= neighborCount;
	vec -= boid.getPos();
	vec.normalize();
	return vec;
}

const Vec2& Application::getCrowdSeperation(const Boid& boid) const {
	Vec2 vec(0, 0);
	int neighborCount = 0;
	for (auto& other : m_boids) {
		if (boid.getPos() != other.getPos()) {
			if (boid.getDistance(other) < m_visionRange / 2) {
				vec += (other.getPos() - boid.getPos());
				neighborCount++;
			}
		}
	}
	if (neighborCount == 0) {
		return vec;
	}
	vec /= neighborCount;
	vec *= -1;
	vec.normalize();
	return vec;
}

const sf::Color& Application::getAverageColor(const Boid& boid) const {
	sf::Color Color = sf::Color::Black;
	int neighborCount = 0;
	for (auto& other : m_boids) {
		if (boid.getPos() != other.getPos()) {
			if (boid.getDistance(other) < m_visionRange) {
				Color += other.getColor();
				neighborCount++;
				Color.r /= neighborCount;
				Color.g /= neighborCount;
				Color.b /= neighborCount;
			}
		}
	}
	if (neighborCount == 0) {
		return boid.getColor();
	}
	
	return Color;
}