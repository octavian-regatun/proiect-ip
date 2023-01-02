#include "lib/AllButtons.hpp"
#include "lib/Button.hpp"
#include "lib/ColorSelector.hpp"
#include "lib/Font.hpp"
#include "lib/Screen.hpp"
#include "lib/ShapeSelector.hpp"
#include "lib/StartMenu.hpp"
#include "lib/Triangulation.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

int main()
{
	unsigned int width = 1000;
	unsigned int height = 1000;

	my::Font::load();

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(width, height), "Morphing - Proiect IP", sf::Style::Default, settings);

	sf::VertexArray superTriangle(sf::Triangles, 3);
	superTriangle[0].position = sf::Vector2f(10.f, 10.f);
	superTriangle[1].position = sf::Vector2f(100.f, 10.f);
	superTriangle[2].position = sf::Vector2f(100.f, 100.f);

	sf::VertexArray miniTriangle(sf::Triangles, 3);
	miniTriangle[0].position = sf::Vector2f(10.f, 10.f);
	miniTriangle[1].position = sf::Vector2f(200.f, 40.f);
	miniTriangle[2].position = sf::Vector2f(101.f, 100.f);

	miniTriangle[0].color = sf::Color::Red;
	miniTriangle[1].color = sf::Color::Red;
	miniTriangle[2].color = sf::Color::Red;

	window.setFramerateLimit(240);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			my::Screen::screenHandler(window, event);
			my::AllButtons::handleEvents(window, event);

			if (event.type == sf::Event::Closed)
				window.close();
		}
		//	window.draw(superTriangle);
		//	window.draw(miniTriangle);
		//	window.draw(lines);
		//	window.display();
	}
	return 0;
}