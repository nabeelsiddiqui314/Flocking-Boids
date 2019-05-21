#pragma once
#include <SFML/Graphics.hpp>

class Boid
{
public:
	Boid(const sf::Vector2f& pos, const sf::Vector2f& dir);
public:
	void update();
	void render(sf::RenderWindow& window);
private:
	float getAngle(const sf::Vector2f& dir);
private:
	sf::Sprite m_boid;
	sf::Texture m_texture;
	std::vector<Boid> m_neighbors;
};

