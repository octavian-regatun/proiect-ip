#include "ShapeSelector.hpp"
#include "AllButtons.hpp"
#include "Clamp.hpp"
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
	// se poate transforma din cerc in triunghi deoarece nu avem clasa pt triunghi
	std::vector<sf::CircleShape>()
};

void ShapeSelector::handleCircleSelection(sf::RenderWindow& window)
{
	unsigned int r;

	std::cout << "Raza: ";
	std::cin >> r;

	clamp(window.getSize().x / 3, 10, r);

	addCircle(window, r);

	setMovingShape();
}

void ShapeSelector::handleRectangleSelection(sf::RenderWindow& window)
{
	unsigned int width, height;

	std::cout << "Latime: ";
	std::cin >> width;

	std::cout << "Inaltime: ";
	std::cin >> height;

	clamp(window.getSize().x / 3, 10, width);
	clamp(window.getSize().y / 3, 10, height);

	addRectangle(window, width, height);

	setMovingShape();
}

void ShapeSelector::handleTriangleSelection(sf::RenderWindow& window)
{
	unsigned int side;

	std::cout << "Latura: ";
	std::cin >> side;

	clamp(window.getSize().x / 3, 10, side);

	addTriangle(window, side);

	setMovingShape();
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

	my::Button rectButton(window, my::Color::buttonColor, length, height, 200, window.getSize().y - 100);
	rectButton.setText(window, my::Color::textColor, "RECTANGLE", my::Font::font, 24);
	rectButton.setOnClick([]() { selectedShape = ShapeType::Rectangle; });

	my::Button circleButton(window, my::Color::buttonColor, length, height, 500, window.getSize().y - 100);
	// sau mai exista susta de a pune spatii in plus ca sa se alinieze😎
	circleButton.setText(window, my::Color::textColor, "CIRCLE   ", my::Font::font, 24);
	circleButton.setOnClick([]() { selectedShape = ShapeType::Circle; });

	my::Button triangleButton(window, my::Color::buttonColor, length, height, 800, window.getSize().y - 100);
	triangleButton.setText(window, my::Color::textColor, "TRIANGLE", my::Font::font, 24);
	triangleButton.setOnClick([]() { selectedShape = ShapeType::Triangle; });
}

void ShapeSelector::handleShapeSelection(sf::RenderWindow& window)
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
		case ShapeType::Nothing:
			break;
		default:
			break;
	}
}
}