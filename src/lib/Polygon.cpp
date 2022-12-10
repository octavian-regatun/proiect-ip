#include "Polygon.hpp"

namespace my
{
std::vector<sf::CircleShape> Polygon::points = std::vector<sf::CircleShape>();

void Polygon::addPoint(sf::RenderWindow& window, sf::Vector2f position)
{

	sf::CircleShape circle;

	circle.setRadius(5);
	circle.setOrigin(5, 5);
	circle.setPosition(position);
	circle.setFillColor(sf::Color::White);

	points.push_back(circle);

	window.draw(circle);
	window.display();
}
}