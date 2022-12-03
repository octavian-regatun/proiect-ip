#include "MyColor.hpp"
#include <SFML/Graphics.hpp>

//tricolorul aplicatiei(se poate schimba pe viitor daca ai o idee mai buna de paleta)
sf::Color MyColor::backgroundColor = sf::Color(44, 62, 80);
sf::Color MyColor::textColor = sf::Color(26, 188, 156);
sf::Color MyColor::buttonColor = sf::Color(22, 160, 133);

int MyColor::colorsCount = 16;
sf::Color* MyColor::colors = new sf::Color[MyColor::colorsCount] { sf::Color(0, 255, 255), sf::Color(0, 0, 0), sf::Color(0, 0, 255), sf::Color(255, 0, 255), sf::Color(128, 128, 128), sf::Color(0, 128, 0), sf::Color(0, 255, 0), sf::Color(128, 0, 0), sf::Color(0, 0, 128), sf::Color(128, 128, 0), sf::Color(128, 0, 128), sf::Color(255, 0, 0), sf::Color(192, 192, 192), sf::Color(0, 128, 128), sf::Color(255, 255, 255), sf::Color(255, 255, 0) };