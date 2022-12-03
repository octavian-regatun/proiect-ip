#include <SFML/Graphics.hpp>

class MyColor
{
public:
	static sf::Color backgroundColor;
	static sf::Color textColor;
	static sf::Color buttonColor;
	static sf::Color* colors;
	static int colorsCount;
};