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

	circle.setOrigin(2, 2);
	circle.setRadius(2);
	circle.setPosition(position);
	circle.setFillColor(sf::Color::White);

	points.push_back(circle);
}

void Polygon::drawLastLine(sf::RenderWindow& window)
{
	if (points.size() > 1)
	{
		sf::Vertex line[] = {
			points.front().getPosition(),
			points.back().getPosition()
		};

		window.draw(line, 2, sf::Lines);
	}
}
}