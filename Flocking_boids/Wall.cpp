#include "stdafx.h"
#include "Wall.h"


Wall::Wall(const Vec2& pos) {
	m_wall.setRadius(8);
	m_wall.setFillColor(sf::Color::Blue);
	m_wall.setPosition(Vec2(pos));
}

const Vec2 Wall::getPos() const {
	return { m_wall.getPosition().x, m_wall.getPosition().y };
}

void Wall::render(sf::RenderWindow& window) {
	window.draw(m_wall);
}