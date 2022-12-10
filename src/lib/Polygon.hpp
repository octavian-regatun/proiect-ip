#pragma once

namespace my
{
class Polygon
{
public:
	static std::vector<sf::CircleShape> points;

public:
	void addPoint(sf::RenderWindow& window, sf::Vector2f position);
};
}