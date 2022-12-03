#include "MyFont.hpp"
#include <SFML/Graphics.hpp>

sf::Font MyFont::font = sf::Font();
sf::Font MyFont::fontBold = sf::Font();

void MyFont::load()
{
	//dam load la fonturile din fisier
	if (!font.loadFromFile("DIN.ttf"))
		std::cout << "ERROR, DIN FONT NOT LOADED";

	if (!fontBold.loadFromFile("DINBold.ttf"))
		std::cout << "ERROR, DINBold FONT NOT LOADED";
}