#include "lib/AllButtons.hpp"
#include "lib/Button.hpp"
#include "lib/ColorSelector.hpp"
#include "lib/Font.hpp"
#include "lib/Screen.hpp"
#include "lib/ShapeSelector.hpp"
#include "lib/StartMenu.hpp"
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

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			my::Screen::screenHandler(window, event);
			my::AllButtons::handleEvents(window, event);

			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered)
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
					for (auto type : my::ShapeSelector::allShapeTypes)
						switch (type)
						{
							case my::ShapeType::Rectangle: {
								std::cout << "rect\n";
							}
							break;
							case my::ShapeType::Circle: {
								std::cout << "circle\n";
							}
							break;
							case my::ShapeType::Triangle: {
								std::cout << "triangle\n";
							}
							break;
							case my::ShapeType::Polygon: {
								std::cout << "polygon\n";
							}
							break;
							case my::ShapeType::Nothing:
								break;
							default:
								break;
						}
		}
	}
	return 0;
}