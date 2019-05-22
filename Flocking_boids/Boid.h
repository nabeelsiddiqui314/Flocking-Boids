#pragma once
#include "Vec2.h"

class Boid
{
public:
	Boid(const Vec2& pos, const Vec2& dir);
public:
	void update();
	void render(sf::RenderWindow& window);

	const Vec2& getDirection() const;
private:
	float getAngle(const Vec2& dir);
private:
	sf::Sprite m_boid;
	sf::Texture m_texture;
	std::vector<Boid> m_neighbors;
	Vec2 m_direction;
	float m_velocity;
};