#include "MyShapeSelector.hpp"
#include "AllButtons.hpp"
#include "lib/MyButton.hpp"
#include "lib/MyColor.hpp"
#include "lib/MyFont.hpp"
#include <SFML/Graphics.hpp>

MyShapeType MyShapeSelector::selectedShape = MyShapeType::Nothing;
MyShapeType MyShapeSelector::currentMovingShape = MyShapeType::Nothing;

MyShapes MyShapeSelector::shapes = {
	0,
	0,
	0,
	new sf::RectangleShape[100],
	new sf::CircleShape[100],
	new sf::CircleShape[100]
};

void MyShapeSelector::refreshShapesCount()
{
	shapes.rectanglesCount = 0;
	shapes.circlesCount = 0;
	shapes.trianglesCount = 0;
}

void MyShapeSelector::displayMenu(sf::RenderWindow& window)
{
	int length = 150, height = 50;

	MyButton rectButton(window, MyColor::buttonColor, length, height, 200, window.getSize().y - 100);
	rectButton.setText(window, MyColor::textColor, "RECTANGLE", MyFont::font, 24);
	rectButton.setOnClick([]() { selectedShape = MyShapeType::Rectangle; });

	MyButton circleButton(window, MyColor::buttonColor, length, height, 500, window.getSize().y - 100);
	// sau mai exista susta de a pune spatii in plus ca sa se alinieze😎
	circleButton.setText(window, MyColor::textColor, "CIRCLE   ", MyFont::font, 24);
	circleButton.setOnClick([]() { selectedShape = MyShapeType::Circle; });

	MyButton triangleButton(window, MyColor::buttonColor, length, height, 800, window.getSize().y - 100);
	triangleButton.setText(window, MyColor::textColor, "TRIANGLE", MyFont::font, 24);
	triangleButton.setOnClick([]() { selectedShape = MyShapeType::Triangle; });
}