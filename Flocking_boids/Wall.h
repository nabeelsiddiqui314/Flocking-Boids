#pragma once
#include <SFML/Graphics.hpp>
#include "Vec2.h"

class Wall
{
public:
	Wall(const Vec2& pos);
	const Vec2 getPos() const;

	void render(sf::RenderWindow& window);
private:
	sf::CircleShape m_wall;
};

