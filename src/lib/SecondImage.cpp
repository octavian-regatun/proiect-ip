#include "SecondImage.hpp"
#include "Button.hpp"
#include "ColorSelector.hpp"
#include "DrawManager.hpp"
#include "Font.hpp"
#include "MenuSelector.hpp"
#include "Screen.hpp"
#include "ShapeSelector.hpp"

namespace my
{

void SecondImage::display(sf::RenderWindow& window)
{
	window.clear(ColorSelector::backgroundColor);
	DrawManager::drawShapes(window);
	SecondImage::moveAllShapes(window);
	SecondImage::movePointsFromPolygon(window);

	window.display();
}

void SecondImage::handleEvents(sf::RenderWindow& window, sf::Event& event)
{
	ShapeSelector::handleShapeSelection(window, event);
	ShapeSelector::handlePolygonFinish(window, event);
	DrawManager::handleEvents(window, event);
}

void SecondImage::displayText(sf::RenderWindow& window)
{
	sf::Text text;

	text.setFont(Font::font);
	text.setString("Second Image");
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setPosition(window.getSize().x / 2 - 50, window.getSize().y - 50);

	window.draw(text);
	window.display();
}

void SecondImage::moveAllShapes(sf::RenderWindow& window)
{
	for (auto& rectangle : ShapeSelector::shapes2.rectangles)
	{
		if (rectangle.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			rectangle.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
			return;
		}
	}

	for (auto& circle : ShapeSelector::shapes2.circles)
	{
		if (circle.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			circle.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
			return;
		}
	}

	for (auto& triangle : ShapeSelector::shapes2.triangles)
	{
		if (triangle.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			triangle.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
			return;
		}
	}
}

void SecondImage::movePointsFromPolygon(sf::RenderWindow& window)
{
	for (auto& polygon : ShapeSelector::shapes2.polygons)
	{
		for (auto& point : polygon.points)
		{
			point.setRadius(2);
			point.setOrigin(2, 2);
			point.setFillColor(sf::Color::White);

			if (point.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				point.setRadius(10);
				point.setOrigin(10, 10);
				point.setFillColor(ColorSelector::buttonColor);
				while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Vector2u pos = DrawManager::setShapeBoundaries(window, point.getLocalBounds(), point.getGlobalBounds());
					point.setPosition(pos.x, pos.y);
				}
			}
		}
	}
}
}