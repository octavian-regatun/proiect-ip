#include "Polygon.hpp"
#include "ColorSelector.hpp"

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
	circle.setFillColor(ColorSelector::activeColor);

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

		line->color = ColorSelector::activeColor;

		window.draw(line, 2, sf::Lines);
	}
}
}