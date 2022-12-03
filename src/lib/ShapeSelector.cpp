#include "ShapeSelector.hpp"
#include "AllButtons.hpp"
#include "lib/Button.hpp"
#include "lib/Color.hpp"
#include "lib/Font.hpp"
#include <SFML/Graphics.hpp>

namespace my
{
ShapeType ShapeSelector::selectedShape = ShapeType::Nothing;
ShapeType ShapeSelector::currentMovingShape = ShapeType::Nothing;

Shapes ShapeSelector::shapes = {
	0,
	0,
	0,
	new sf::RectangleShape[100],
	new sf::CircleShape[100],
	new sf::CircleShape[100]
};

void ShapeSelector::refreshShapesCount()
{
	shapes.rectanglesCount = 0;
	shapes.circlesCount = 0;
	shapes.trianglesCount = 0;
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
}