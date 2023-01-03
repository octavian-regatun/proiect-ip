#include "SecondImage.hpp"
#include "Button.hpp"
#include "ColorSelector.hpp"
#include "DrawManager.hpp"
#include "Font.hpp"
#include "MenuSelector.hpp"
#include "Morphing.hpp"
#include "SavingImage.hpp"
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
	Morphing::displayMorphingButton(window);

	window.display();
}

void SecondImage::handleEvents(sf::RenderWindow& window, sf::Event& event)
{
	//ShapeSelector::handleShapeSelection(window, event);
	//ShapeSelector::handlePolygonFinish(window, event);
	//DrawManager::handleEvents(window, event);
	saveSecondImage();
}

void SecondImage::displayText(sf::RenderWindow& window)
{
	sf::Text text;

	text.setFont(Font::font);
	text.setString("Second Image");
	text.setCharacterSize(20);
	text.setFillColor(ColorSelector::textColor);
	text.setPosition(window.getSize().x / 2 - 50, window.getSize().y - 30);

	window.draw(text);
	window.display();
}

void SecondImage::moveAllShapes(sf::RenderWindow& window)
{

	for (int i = ShapeSelector::shapes2.rectangles.size() - 1; i >= 0; i--)
	{
		auto& rectangle = ShapeSelector::shapes2.rectangles[i];

		if (rectangle.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{

			while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				window.clear(ColorSelector::backgroundColor);
				DrawManager::drawShapes(window);
				sf::Vector2u pos = DrawManager::setShapeBoundaries(window, rectangle.getLocalBounds(), rectangle.getGlobalBounds());
				rectangle.setPosition(pos.x, pos.y);

				window.draw(rectangle);
				displayText(window);
			}
		}
	}

	for (int i = ShapeSelector::shapes2.circles.size() - 1; i >= 0; i--)
	{
		auto& circle = ShapeSelector::shapes2.circles[i];

		if (circle.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				window.clear(ColorSelector::backgroundColor);
				DrawManager::drawShapes(window);
				sf::Vector2u pos = DrawManager::setShapeBoundaries(window, circle.getLocalBounds(), circle.getGlobalBounds());
				circle.setPosition(pos.x, pos.y);

				window.draw(circle);
				displayText(window);
			}
		}
	}

	for (int i = ShapeSelector::shapes2.triangles.size() - 1; i >= 0; i--)
	{
		auto& triangle = ShapeSelector::shapes2.triangles[i];
		if (triangle.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				window.clear(ColorSelector::backgroundColor);
				DrawManager::drawShapes(window);
				sf::Vector2u pos = DrawManager::setShapeBoundaries(window, triangle.getLocalBounds(), triangle.getGlobalBounds());
				triangle.setPosition(pos.x, pos.y);

				window.draw(triangle);
				displayText(window);
			}
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
			point.setFillColor(polygon.polygonColor);

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
void SecondImage::saveSecondImage()
{
	static int ok = 0;
	if (ok)
		return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		ok = 1;
		SavingImage::saveSecondImage();
		std::cout << "llllll";
	}
}
}