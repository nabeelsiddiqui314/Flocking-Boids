#include "stdafx.h"
#include "Boid.h"

Boid::Boid(const Vec2& pos, const Vec2& dir, const sf::Color& color)
: m_direction(dir), m_velocity(2) {
	m_texture = std::make_shared<sf::Texture>();
	m_texture->loadFromFile("res/boid.png");
	m_boid.setTexture(*m_texture);
	m_boid.setPosition(Vec2(pos));
	m_boid.setOrigin(m_boid.getGlobalBounds().width / 2,
		             m_boid.getGlobalBounds().height / 2);
	m_direction.normalize();
	m_boid.setRotation(this->getAngle(m_direction) + 90);
	m_boid.setColor(color);
}

void Boid::update(const Vec2& dir) {
	m_direction += dir;
	m_direction.normalize();
	m_boid.setRotation(this->getAngle(m_direction) + 90);
	m_boid.move(Vec2(m_direction * m_velocity));
}

void Boid::render(sf::RenderWindow& window) {
	window.draw(m_boid);
}

void Boid::setPos(const Vec2& pos) {
	m_boid.setPosition(Vec2(pos));
}

void Boid::setColor(const sf::Color& color) {
	m_boid.setColor(color);
}

float Boid::getDistance(const Boid& boid) const {
	return sqrt(pow(this->getPos().x - boid.getPos().x, 2) + pow(this->getPos().y - boid.getPos().y, 2));
}

const Vec2 Boid::getPos() const {
	return { m_boid.getPosition().x, m_boid.getPosition().y };
}

const sf::Color& Boid::getColor() const {
	return m_boid.getColor();
}

const Vec2& Boid::getDirection() const {
	return m_direction;
}

float Boid::getAngle(const Vec2& dir) {
	return atan2f(dir.y, dir.x) * 57.2958f;
}