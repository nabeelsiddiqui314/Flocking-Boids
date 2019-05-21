#include "stdafx.h"
#include "Boid.h"


Boid::Boid(const sf::Vector2f& pos, const sf::Vector2f& dir) {
	m_texture.loadFromFile("res/boid.png");
	m_boid.setTexture(m_texture);
	m_boid.setPosition(pos);
	m_boid.setOrigin(m_boid.getGlobalBounds().width / 2,
		             m_boid.getGlobalBounds().height / 2);
	m_boid.setRotation(this->getAngle(dir));
}

void Boid::update() {

}

void Boid::render(sf::RenderWindow& window) {
	window.draw(m_boid);
}

float Boid::getAngle(const sf::Vector2f& dir) {
	return atan2f(dir.y, dir.x) * 57.2958f;
}