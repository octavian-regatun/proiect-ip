#include "Color.hpp"
#include <SFML/Graphics.hpp>

namespace my
{
//tricolorul aplicatiei(se poate schimba pe viitor daca ai o idee mai buna de paleta)
sf::Color my::Color::backgroundColor = sf::Color(44, 62, 80);
sf::Color my::Color::textColor = sf::Color(236, 240, 241);
sf::Color my::Color::buttonColor = sf::Color(22, 160, 133);

int my::Color::colorsCount = 16;
sf::Color* my::Color::colors = new sf::Color[my::Color::colorsCount] { sf::Color(0, 255, 255), sf::Color(0, 0, 0), sf::Color(0, 0, 255), sf::Color(255, 0, 255), sf::Color(128, 128, 128), sf::Color(0, 128, 0), sf::Color(0, 255, 0), sf::Color(128, 0, 0), sf::Color(0, 0, 128), sf::Color(128, 128, 0), sf::Color(128, 0, 128), sf::Color(255, 0, 0), sf::Color(192, 192, 192), sf::Color(0, 128, 128), sf::Color(255, 255, 255), sf::Color(255, 255, 0) };
}