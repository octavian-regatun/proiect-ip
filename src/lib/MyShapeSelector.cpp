#include "MyShapeSelector.hpp"
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
	shapes.rectangleCount = 0;
	shapes.circleCount = 0;
	shapes.triangleCount = 0;
}

// struct menuBtns
// {
// 	int counter = 0; //checks how many buttons are in a menu
// 	sf::RectangleShape btns[10];
// 	sf::Text text[10];
// };
// menuBtns Mbuttons[2]; //vectorul este pentru a separa butoanele in functie de meniul din care fac parte ex: Mbuttons[0] pentru toate butoanele din MainMenu

// MyShapeSelector::display(sf::RenderWindow& window)
// {
// 	int length = 150;
// 	int height = 50;

// 	MyButton rectButton(window, MyColor::buttonColor, length, height, 200, window.getSize().y - 100);
// 	rectButton.setText(window, MyColor::textColor, "RECTANGLE", MyFont::font, 24);
// 	Mbuttons[1].btns[0] = rectButton.button;
// 	Mbuttons[1].text[0] = rectButton.text;

// 	MyButton circleButton(window, MyColor::buttonColor, length, height, 500, window.getSize().y - 100);
// 	circleButton.setText(window, MyColor::textColor, "CIRCLE   ", MyFont::font, 24); //sau mai exista susta de a pune spatii in plus ca sa se alinieze😎
// 	Mbuttons[1].btns[1] = circleButton.button;
// 	Mbuttons[1].text[1] = circleButton.text;

// 	MyButton triangleButton(window, MyColor::buttonColor, length, height, 800, window.getSize().y - 100);
// 	triangleButton.setText(window, MyColor::textColor, "TRIANGLE", MyFont::font, 24);
// 	Mbuttons[1].btns[2] = triangleButton.button;
// 	Mbuttons[1].text[2] = triangleButton.text;

// 	Mbuttons[1].counter = 3;
// }