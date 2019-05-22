#include "stdafx.h"
#include "Application.h"


Application::Application() {
	srand(time(NULL));
}

void Application::update(const sf::RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_mousePressedLast) {
		Boid b( {(float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y },
			    { (float)(rand() % 10) - 5.0f, (float)(rand() % 10) - 5.0f });
		m_boids.push_back(b);
	}
	m_mousePressedLast = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	for (auto& boid : m_boids) {
		Vec2 direction(0.5,0.2);
		for (auto& other : m_boids) {
			
		}
		boid.update(direction);
	}
}

void Application::render(sf::RenderWindow& window) {
	for (auto& boid : m_boids) {
		boid.render(window);
	}
}