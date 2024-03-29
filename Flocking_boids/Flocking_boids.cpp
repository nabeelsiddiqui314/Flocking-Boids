#include "stdafx.h"
#include "Application.h"

int main() {
	sf::RenderWindow window;
	sf::Clock        clock;
	sf::Time         accumulator = sf::Time::Zero;
	sf::Time         ups = sf::seconds(1.f / 60.f);
	Application      app;

	window.create(sf::VideoMode(1000, 650), "Flocking Boids");

	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color(180, 180, 180));
		while (accumulator > ups) {
			accumulator -= ups;
			app.update(window);
		}
		accumulator += clock.restart();
		app.render(window);
		window.display();
	}
	return 0;
}