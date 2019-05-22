#pragma once
#include <memory>
#include "Vec2.h"

class Boid
{
public:
	Boid(const Vec2& pos, const Vec2& dir);
public:
	void update(const Vec2& dir);
	void render(sf::RenderWindow& window);
	void setPosition(const Vec2& pos);

	float getDistance(const Boid& boid) const;
	const Vec2& getDirection() const;
	const Vec2 getPos() const;
private:
	float getAngle(const Vec2& dir);
private:
	sf::Sprite m_boid;
	std::shared_ptr<sf::Texture> m_texture;
	Vec2 m_direction;
	float m_velocity;
};