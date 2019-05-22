#include "stdafx.h"
#include "Boid.h"


Boid::Boid(const Vec2& pos, const Vec2& dir)
: m_velocity(2) {
	m_texture.loadFromFile("res/boid.png");
	m_boid.setTexture(m_texture);
	m_boid.setPosition(Vec2(pos));
	m_boid.setOrigin(m_boid.getGlobalBounds().width / 2,
		             m_boid.getGlobalBounds().height / 2);
	m_direction.normalise();
	m_boid.setRotation(this->getAngle(m_direction));
}

void Boid::update() {
	m_boid.move(Vec2(m_direction));
}

void Boid::render(sf::RenderWindow& window) {
	window.draw(m_boid);
}

const Vec2& Boid::getDirection() const {
	return m_direction;
}

float Boid::getAngle(const Vec2& dir) {
	return atan2f(dir.y, dir.x) * 57.2958f;
}