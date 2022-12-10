#include "Polygon.hpp"

namespace my
{

Polygon::Polygon()
{
	isFinished = false;
	points = std::vector<sf::CircleShape>();
}

void Polygon::addPoint(sf::RenderWindow& window, sf::Vector2f position)
{

	sf::CircleShape circle;

	circle.setOrigin(5, 5);
	circle.setRadius(5);
	circle.setPosition(position);
	circle.setFillColor(sf::Color::White);

	points.push_back(circle);
}
}