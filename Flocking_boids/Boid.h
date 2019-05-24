#pragma once
#include <memory>
#include "Vec2.h"

class Boid
{
public:
	Boid(const Vec2& pos, const Vec2& dir, bool isPredator);
public:
	void update(const Vec2& dir);
	void render(sf::RenderWindow& window);
	void setPos(const Vec2& pos);
	void setColor(const sf::Color& color);

	float getDistance(const Boid& boid) const;
	const Vec2& getDirection() const;
	const Vec2 getPos() const;
	const sf::Color& getColor() const;
	bool isPredator() const;
private:
	float getAngle(const Vec2& dir);
private:
	sf::Sprite m_boid;
	std::shared_ptr<sf::Texture> m_texture;
	Vec2 m_direction;
	float m_velocity;
	bool m_isPredator;
};