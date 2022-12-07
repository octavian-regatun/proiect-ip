#include "DrawManager.hpp"
#include "ShapeSelector.hpp"

namespace my
{
void DrawManager::drawShapes(sf::RenderWindow& window)
{
	for (auto& rectangle : ShapeSelector::shapes.rectangles)
	{
		window.draw(rectangle);
	}

	for (auto& circle : ShapeSelector::shapes.circles)
	{
		window.draw(circle);
	}

	for (auto& triangle : ShapeSelector::shapes.triangles)
	{
		window.draw(triangle);
	}
}

void DrawManager::handleEvents(sf::RenderWindow& window, sf::Event& event)
{
	// while left click is being hold down
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		moveShape(window, event);
	}

	savePosition(window, event);
}

void DrawManager::moveShape(sf::RenderWindow& window, sf::Event& event)
{
	switch (ShapeSelector::movingShape)
	{
		case ShapeType::Rectangle:
			ShapeSelector::shapes.rectangles.back().setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			break;
		case ShapeType::Circle:
			ShapeSelector::shapes.circles.back().setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			break;
		case ShapeType::Triangle:
			ShapeSelector::shapes.triangles.back().setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			break;
	}
}

void DrawManager::savePosition(sf::RenderWindow& window, sf::Event& event)
{
	// when pressed enter save the position of the shape
	if (event.key.code == sf::Keyboard::Enter)
	{
		ShapeSelector::movingShape = ShapeType::Nothing;
		ShapeSelector::selectedShape = ShapeType::Nothing;
	}
}
}