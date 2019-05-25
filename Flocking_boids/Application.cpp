#include "stdafx.h"
#include "Application.h"


Application::Application()
: m_visionRange(100),
  m_predatorVisionRange(400),
  m_wallAvoidDist(100) {
	srand(time(NULL));
}

void Application::update(const sf::RenderWindow& window) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !m_spacePressedLast) {
		m_walls.emplace_back(Vec2((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y));
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_LmousePressedLast) ||
		(sf::Mouse::isButtonPressed(sf::Mouse::Right) && !m_RmousePressedLast)) {
		bool isPredator = sf::Mouse::isButtonPressed(sf::Mouse::Right);

		Boid b({ (float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y },
			{ (float)(rand() % 10) - 5.0f, (float)(rand() % 10) - 5.0f }, isPredator);
		if (isPredator)
			b.setColor(sf::Color::Red);
		else
			b.setColor(sf::Color::Green);
		m_boids.push_back(b);
	}

	m_LmousePressedLast = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	m_RmousePressedLast = sf::Mouse::isButtonPressed(sf::Mouse::Right);
	m_spacePressedLast = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	for (auto& boid : m_boids) {
		Vec2 direction(0,0);
		direction += this->getAllignment(boid);
		direction += this->getCohesion(boid);
		direction += this->getCrowdSeperation(boid);
		direction += this->getPredatorAvoidance(boid);
		direction += this->getWallAvoidance(boid);

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
	for (auto& wall : m_walls) {
		wall.render(window);
	}
}

const Vec2 Application::getAllignment(const Boid& boid) const {
	Vec2 vec(0,0);
	int neighborCount = 0;
	for (auto& other : m_boids) {
		if (boid.getPos() != other.getPos()) {
			if (boid.isPredator() == other.isPredator() && boid.getDistance(other) < m_visionRange) {
				vec += other.getDirection();
				neighborCount++;
			}
			else if (boid.isPredator() && !other.isPredator() && boid.getDistance(other) < m_predatorVisionRange) {
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

const Vec2 Application::getCohesion(const Boid& boid) const {
	Vec2 vec(0, 0);
	int neighborCount = 0;
	for (auto& other : m_boids) {
		if (boid.getPos() != other.getPos()) {
			if (boid.isPredator() == other.isPredator() && boid.getDistance(other) < m_visionRange) {
				vec += other.getPos();
				neighborCount++;
			}
			else if (boid.isPredator() && !other.isPredator() && boid.getDistance(other) < m_predatorVisionRange) {
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

const Vec2 Application::getCrowdSeperation(const Boid& boid) const {
	Vec2 vec(0, 0);
	int neighborCount = 0;
	for (auto& other : m_boids) {
		if (boid.getPos() != other.getPos()) {
			if (boid.isPredator() == other.isPredator() && boid.getDistance(other) < m_visionRange / 2) {
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

const Vec2 Application::getPredatorAvoidance(const Boid& boid) const {
	Vec2 vec(0,0);
	int predatorCount = 0;
	if (!boid.isPredator()) {
		for ( auto& predator : m_boids) {
			if (!predator.isPredator() || boid.getDistance(predator) > m_visionRange)
				continue;
			vec += (predator.getPos() - boid.getPos());
			predatorCount++;
		}
		if (predatorCount == 0)
			return vec;
		vec /= predatorCount;
		vec *= -1;
		vec.normalize();
		return vec;
	}
	return vec;
}

const Vec2 Application::getWallAvoidance(const Boid& boid) const {
	Vec2 vec(0,0);
	int wallCount = 0;
	for (auto& wall : m_walls) {
		if (boid.getDistance(wall.getPos()) < m_wallAvoidDist) {
			vec += (wall.getPos() - boid.getPos());
			wallCount++;
		}
	}
	if (wallCount == 0) {
		return vec;
	}
	vec /= wallCount;
	vec *= -1;
	vec.normalize();
	return vec;
}
