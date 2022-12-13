#pragma once
#include <SFML/Graphics.hpp>

namespace my
{
class ColorSelector
{
public:
	static sf::Color backgroundColor;
	static sf::Color textColor;
	static sf::Color buttonColor;
	static sf::Color activeColor;

	static std::vector<sf::Color> colors;

	static void displayMenu(sf::RenderWindow& window);
};
}