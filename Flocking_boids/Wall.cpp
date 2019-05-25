#include "stdafx.h"
#include "Wall.h"


Wall::Wall(const Vec2& pos) {
	m_circle.setRadius(8);
	m_circle.setFillColor(sf::Color::Blue);
	m_circle.setPosition(Vec2(pos));
}

const Vec2 Wall::getPos() const {
	return { m_circle.getPosition().x, m_circle.getPosition().y };
}

void Wall::render(sf::RenderWindow& window) {
	window.draw(m_circle);
}