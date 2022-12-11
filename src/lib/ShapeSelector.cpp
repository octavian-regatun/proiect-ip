#include "ShapeSelector.hpp"
#include "AllButtons.hpp"
#include "Clamp.hpp"
#include "Polygon.hpp"
#include "ShapeSettings.hpp"
#include "Timer.hpp"
#include "lib/Button.hpp"
#include "lib/Color.hpp"
#include "lib/Font.hpp"
#include <SFML/Graphics.hpp>

namespace my
{
ShapeType ShapeSelector::selectedShape = ShapeType::Nothing;
ShapeType ShapeSelector::movingShape = ShapeType::Nothing;

Shapes ShapeSelector::shapes = {
	std::vector<sf::RectangleShape>(),
	std::vector<sf::CircleShape>(),
	std::vector<sf::CircleShape>(),
	std::vector<Polygon>()
};

void ShapeSelector::handleCircleSelection(sf::RenderWindow& window)
{
	if (movingShape != ShapeType::Nothing)
		return;
	unsigned int r;

	r = ShapeSettings::setCircleSettings(window, "Radius"); //pops up the settings for the shape

	clamp(window.getSize().x / 3, 10, r);

	addCircle(window, r);

	setMovingShape();
}

void ShapeSelector::handleRectangleSelection(sf::RenderWindow& window)
{
	if (movingShape != ShapeType::Nothing)
		return;

	unsigned int width, height;

	ShapeSettings::setRectangleSettings(window, width, height);

	clamp(window.getSize().x / 3, 10, width);
	clamp(window.getSize().y / 3, 10, height);

	addRectangle(window, width, height);

	setMovingShape();
}

void ShapeSelector::handleTriangleSelection(sf::RenderWindow& window)
{
	if (movingShape != ShapeType::Nothing)
		return;

	unsigned int side;

	side = ShapeSettings::setCircleSettings(window, "Side"); //pops up the settings for the shape

	clamp(window.getSize().x / 3, 10, side);

	addTriangle(window, side);

	setMovingShape();
}

void ShapeSelector::handlePolygonSelection(sf::RenderWindow& window, sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		Polygon polygon;

		ShapeSelector::shapes.polygons.push_back(polygon);

		setMovingShape();
	}
}

void ShapeSelector::setMovingShape()
{
	movingShape = selectedShape;
	selectedShape = ShapeType::Nothing;
}

void ShapeSelector::addCircle(sf::RenderWindow& window, unsigned int radius)
{
	sf::CircleShape circle;

	circle.setRadius(radius);
	circle.setOrigin(radius, radius);
	circle.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

	shapes.circles.push_back(circle);

	window.draw(circle);
	window.display();
}

void ShapeSelector::addRectangle(sf::RenderWindow& window, unsigned int width, unsigned int height)
{
	sf::RectangleShape rectangle;

	rectangle.setSize(sf::Vector2f(width, height));
	rectangle.setOrigin(width / 2.f, height / 2.f);
	rectangle.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

	shapes.rectangles.push_back(rectangle);

	window.draw(rectangle);
	window.display();
}

void ShapeSelector::addTriangle(sf::RenderWindow& window, unsigned int side)
{
	sf::CircleShape triangle;

	triangle.setRadius(side);
	triangle.setPointCount(3);
	triangle.setOrigin(side, side);
	triangle.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

	shapes.triangles.push_back(triangle);

	window.draw(triangle);
	window.display();
}

void ShapeSelector::refreshShapesCount()
{
	shapes.rectangles.clear();
	shapes.circles.clear();
	shapes.triangles.clear();
}

void ShapeSelector::displayMenu(sf::RenderWindow& window)
{
	int length = 150, height = 50;

	my::Button rectButton(window, my::Color::buttonColor, length, height, 125, window.getSize().y - 100);
	rectButton.setText(window, my::Color::textColor, "RECTANGLE", my::Font::font, 24);
	rectButton.setOnClick([]() { selectedShape = ShapeType::Rectangle; });

	my::Button circleButton(window, my::Color::buttonColor, length, height, 375, window.getSize().y - 100);
	// sau mai exista susta de a pune spatii in plus ca sa se alinieze😎
	circleButton.setText(window, my::Color::textColor, "CIRCLE  ", my::Font::font, 24);
	circleButton.setOnClick([]() { selectedShape = ShapeType::Circle; });

	my::Button triangleButton(window, my::Color::buttonColor, length, height, 625, window.getSize().y - 100);
	triangleButton.setText(window, my::Color::textColor, "TRIANGLE", my::Font::font, 24);
	triangleButton.setOnClick([]() { selectedShape = ShapeType::Triangle; });

	my::Button polygonButton(window, my::Color::buttonColor, length, height, 875, window.getSize().y - 100);
	polygonButton.setText(window, my::Color::textColor, "POLYGON", my::Font::font, 24);
	polygonButton.setOnClick([]() { selectedShape = ShapeType::Polygon; });
}

void ShapeSelector::handleShapeSelection(sf::RenderWindow& window, sf::Event& event)
{
	switch (selectedShape)
	{
		case ShapeType::Rectangle:
			handleRectangleSelection(window);
			break;
		case ShapeType::Circle:
			handleCircleSelection(window);
			break;
		case ShapeType::Triangle:
			handleTriangleSelection(window);
			break;
		case ShapeType::Polygon:
			handlePolygonSelection(window, event);
			break;
		case ShapeType::Nothing:
			break;
		default:
			break;
	}
}
}