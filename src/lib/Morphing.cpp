#include "Morphing.hpp"
#include "Button.hpp"
#include "ColorSelector.hpp"
#include "Font.hpp"
#include "ShapeSelector.hpp"
#include <cassert>
#include <cmath>

namespace my
{
void Morphing::displayMorphingButton(sf::RenderWindow& window)
{
	Button button = Button(window, ColorSelector::buttonColor, 200, 50, window.getSize().x / 2 + 15, window.getSize().y - 75);
	button.setText(window, sf::Color::White, "START MORPHING", Font::font, 20);

	if (button.button.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		std::cout << "Morphing started...";
		animateAllShapes(window, 5000);
		std::cout << "Morphing ended...";
	}
}

float Morphing::lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

void Morphing::animateAllShapes(sf::RenderWindow& window, unsigned int ms)
{
	sf::Clock clock;
	while (clock.getElapsedTime().asMilliseconds() < ms)
	{
		float progress = (float)clock.getElapsedTime().asMilliseconds() / ms;
		for (int i = 0; i < ShapeSelector::shapes.circles.size(); i++)
		{
			animateCircle(window, ShapeSelector::shapes.circles[i], { ShapeSelector::shapes2.circles[i].getPosition().x, ShapeSelector::shapes2.circles[i].getPosition().y }, progress);
		}
		for (int i = 0; i < ShapeSelector::shapes.rectangles.size(); i++)
		{
			animateRectangle(window, ShapeSelector::shapes.rectangles[i], { ShapeSelector::shapes2.rectangles[i].getPosition().x, ShapeSelector::shapes2.rectangles[i].getPosition().y }, progress);
		}
		window.clear(ColorSelector::backgroundColor);
	}
}

void Morphing::animateCircle(sf::RenderWindow& window, sf::CircleShape& circle, sf::Vector2u finalPoint, float progress)
{
	sf::Vector2u initialPoint = { circle.getPosition().x, circle.getPosition().y };
	sf::Vector2u distance = { finalPoint.x - initialPoint.x, finalPoint.y - initialPoint.y };

	circle.setPosition(lerp(initialPoint.x, finalPoint.x, progress), lerp(initialPoint.y, finalPoint.y, progress));

	window.draw(circle);
	window.display();
}

void Morphing::animateRectangle(sf::RenderWindow& window, sf::RectangleShape& rectangle, sf::Vector2u finalPoint, float progress)
{
	sf::Vector2u initialPoint = { rectangle.getPosition().x, rectangle.getPosition().y };
	sf::Vector2u distance = { finalPoint.x - initialPoint.x, finalPoint.y - initialPoint.y };

	rectangle.setPosition(lerp(initialPoint.x, finalPoint.x, progress), lerp(initialPoint.y, finalPoint.y, progress));

	window.draw(rectangle);
	window.display();
}
}