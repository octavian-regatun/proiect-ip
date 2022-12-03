#pragma once
#include <SFML/Graphics.hpp>

class MyButton
{
private:
	std::function<void()> onClick;

public:
	sf::RectangleShape button;
	sf::Text text;
	MyButton(sf::RenderWindow& window, sf::Color fillColor, int length, int height, int x, int y);
	void setText(sf::RenderWindow& window, sf::Color color, std::string txt, sf::Font font, int chSize);
	void setOnClick(std::function<void()> onClick);
	std::function<void()> getOnClick();
};
