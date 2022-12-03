#include "lib/MyButton.hpp"
#include "lib/MyColor.hpp"
#include "lib/MyFont.hpp"
#include "lib/MyScreen.hpp"
#include "lib/MyShapeSelector.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

sf::String playerInput;
sf::Text playerText;

struct menuBtns
{
	int counter = 0; //checks how many buttons are in a menu
	RectangleShape btns[10];
	Text text[10];
};
menuBtns Mbuttons[2]; //vectorul este pentru a separa butoanele in functie de meniul din care fac parte ex: Mbuttons[0] pentru toate butoanele din MainMenu
void CreateMenuButtons(RenderWindow& window);
void CreateImagesMenu(RenderWindow& window);
void Menu(RenderWindow& window);
bool isMousePressed(RenderWindow& window, RectangleShape collider);
bool exitTimer(); //avem nevoie de timer deoarece cand dam esc si nu avem timer se va apela de mai multe ori exit-ul
void Clamp(unsigned int max, unsigned int min, unsigned int& value);
void DisplayShapes(RenderWindow& window);

void CreateMenuButtons(RenderWindow& window)
{
	int length = 150;
	int height = 50;

	MyButton rectButton(window, MyColor::buttonColor, length, height, 200, window.getSize().y - 100);
	rectButton.setText(window, MyColor::textColor, "RECTANGLE", MyFont::font, 24);
	Mbuttons[1].btns[0] = rectButton.button;
	Mbuttons[1].text[0] = rectButton.text;

	MyButton circleButton(window, MyColor::buttonColor, length, height, 500, window.getSize().y - 100);
	circleButton.setText(window, MyColor::textColor, "CIRCLE   ", MyFont::font, 24); //sau mai exista susta de a pune spatii in plus ca sa se alinieze😎
	Mbuttons[1].btns[1] = circleButton.button;
	Mbuttons[1].text[1] = circleButton.text;

	MyButton triangleButton(window, MyColor::buttonColor, length, height, 800, window.getSize().y - 100);
	triangleButton.setText(window, MyColor::textColor, "TRIANGLE", MyFont::font, 24);
	Mbuttons[1].btns[2] = triangleButton.button;
	Mbuttons[1].text[2] = triangleButton.text;

	Mbuttons[1].counter = 3;
}

void DisplayShapes(RenderWindow& window)
{
	for (int i = 0; i < MyShapeSelector::shapes.rectangleCount; i++)
		window.draw(MyShapeSelector::shapes.rectangles[i]);
	for (int i = 0; i < MyShapeSelector::shapes.circleCount; i++)
		window.draw(MyShapeSelector::shapes.circles[i]);
	for (int i = 0; i < MyShapeSelector::shapes.triangleCount; i++)
		window.draw(MyShapeSelector::shapes.triangles[i]);

	window.display();
}
void Clamp(unsigned int max, unsigned int min, unsigned int& value)
{
	if (value > max)
		value = max;
	else if (value <= min)
		value = min;
}
bool exitTimer()
{
	Clock clock;
	float elapsedTime = clock.getElapsedTime().asSeconds();
	while (elapsedTime < .5f)
		elapsedTime = clock.getElapsedTime().asSeconds();

	return false;
}
bool isMousePressed(RenderWindow& window, RectangleShape collider)
{
	if (Mouse::isButtonPressed(Mouse::Left))
		if (collider.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
			return true;

	return false;
}
void Menu(RenderWindow& window)
{
	//reinitializam shapeCounterurile cand ajungem iarasi in Menu
	MyShapeSelector::refreshShapesCount();

	//background color
	window.clear(MyColor::backgroundColor);
	MyScreen::goToScreen(MyScreenEnum::Start);

	int x = window.getSize().x / 2.f;
	int y = window.getSize().y / 2.f;

	//Title
	Text title;

	title.setString("MENU");
	title.setFont(MyFont::fontBold);
	title.setCharacterSize(70);
	title.setPosition(x - 100, 100);
	title.setFillColor(MyColor::textColor);
	window.draw(title);

	//button for create feature
	int length = 200;
	int height = 50;

	MyButton createButton(window, MyColor::buttonColor, length, height, x, y);
	createButton.setText(window, MyColor::textColor, "CREATE IMAGE", MyFont::font, 24); //ca textul sa se incadreze in centrul butonului ar trebui sa schimbi valorile length,height sau chSize(24)

	Mbuttons[0].btns[0] = createButton.button;
	Mbuttons[0].text[0] = createButton.text;
	Mbuttons[0].counter = 1;

	window.display();
}
void CreateImagesMenu(RenderWindow& window)
{
	window.clear(MyColor::backgroundColor);
	MyScreen::goToScreen(MyScreenEnum::FirstImage);

	CreateMenuButtons(window);

	window.display();
}
int main()
{
	unsigned int width = 1000;
	unsigned int height = 1000;

	sf::RenderWindow window(sf::VideoMode(width, height), "Morphing - Proiect IP");

	MyFont::load();

	Menu(window);

	bool isPressed = false;

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			switch (event.type)
			{
				case Event::Closed:
					window.close();
					break;

				default:
					break;
			}
			switch (MyScreen::currentScreen) //butoanele vor functiona in functie de meniul curent
			{
				case 0: {

					RectangleShape collider = Mbuttons[MyScreen::currentScreen].btns[0]; //butonul de createImage

					if (isMousePressed(window, collider)) //check if mouse is pressed on the button
					{
						CreateImagesMenu(window);
					}
					else if (Keyboard::isKeyPressed(Keyboard::Escape) && !isPressed)
					{
						isPressed = true;
						window.close();
					}

					break;
				}
				case 1: {
					RectangleShape rectangleBtn = Mbuttons[MyScreen::currentScreen].btns[0];
					RectangleShape circleBtn = Mbuttons[MyScreen::currentScreen].btns[1];
					RectangleShape triangleBtn = Mbuttons[MyScreen::currentScreen].btns[2];

					if (isMousePressed(window, rectangleBtn))
					{
						MyShapeSelector::selectedShape = MyShapeType::Rectangle;
					}
					else if (isMousePressed(window, circleBtn))
					{
						MyShapeSelector::selectedShape = MyShapeType::Circle;
					}
					else if (isMousePressed(window, triangleBtn))
					{
						MyShapeSelector::selectedShape = MyShapeType::Triangle;
					}

					switch (MyShapeSelector::selectedShape) //scuze pt atatea switch/if dar sincer nu stiu cum sa fac altcumva :)
					{
						case MyShapeType::Rectangle: {

							unsigned int h, l;
							cout << "Inaltimea: ";
							cin >> h;
							cout << "Lungimea: ";
							cin >> l;
							//aici poti daca vrei sa intrebi ce culoare ar dori(doar o idee)

							Clamp(width - 300, 10, l);
							Clamp(height - 300, 10, h);

							CreateImagesMenu(window);
							MyShapeSelector::shapes.rectangleCount++;
							MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].setSize(Vector2f(l, h));
							MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].setOrigin(l / 2.f, h / 2.f);
							MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].setPosition(width / 2.f, height / 2.f);

							window.draw(MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1]);
							window.display();

							MyShapeSelector::currentMovingShape = MyShapeSelector::selectedShape;
							MyShapeSelector::selectedShape = MyShapeType::Nothing; //la final reinitializam shapeType cu n pentru a finaliza procesul de creare
							break;
						}
						case MyShapeType::Circle: {

							unsigned int r;
							cout << "Raza: ";
							cin >> r;

							Clamp(width / 3, 10, r);

							CreateImagesMenu(window);

							MyShapeSelector::shapes.circleCount++;

							MyShapeSelector::shapes.circles[MyShapeSelector::shapes.circleCount - 1].setRadius(r);
							MyShapeSelector::shapes.circles[MyShapeSelector::shapes.circleCount - 1].setOrigin(r, r);
							MyShapeSelector::shapes.circles[MyShapeSelector::shapes.circleCount - 1].setPosition(width / 2.f, height / 2.f);

							window.draw(MyShapeSelector::shapes.circles[MyShapeSelector::shapes.circleCount - 1]);
							window.display();

							MyShapeSelector::currentMovingShape = MyShapeSelector::selectedShape;
							MyShapeSelector::selectedShape = MyShapeType::Nothing;
							break;
						}
						case MyShapeType::Triangle: {
							unsigned int l;
							cout << "Latura: ";
							cin >> l;

							Clamp(width / 3, 10, l);

							CreateImagesMenu(window);

							MyShapeSelector::shapes.triangleCount++;
							MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].setRadius(l);
							MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].setPointCount(3);
							MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].setOrigin(l, l);
							MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].setPosition(width / 2.f, height / 2.f);

							window.draw(MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.circleCount - 1]);
							window.display();

							MyShapeSelector::currentMovingShape = MyShapeSelector::selectedShape;
							MyShapeSelector::selectedShape = MyShapeType::Nothing;
							break;
						}

						default:
							break;
					}

					switch (MyShapeSelector::currentMovingShape) //aici se misca obiectul
					{
						case MyShapeType::Rectangle: {
							if (Mouse::isButtonPressed(Mouse::Left))
							{
								window.clear(MyColor::backgroundColor);

								unsigned int x = Mouse::getPosition(window).x;
								unsigned int y = Mouse::getPosition(window).y;

								if (x > width * 10) //e ceva bug in care din stanga se teleporteaza in dreapta?
									x = 0;
								if (y > height * 10)
									y = 0;

								//limitele in care se poate misca obietul
								Clamp(width - MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].getGlobalBounds().width + MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].getLocalBounds().width / 2.f, MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].getLocalBounds().width / 2.f, x);
								Clamp(height - 200 - MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].getGlobalBounds().height + MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].getLocalBounds().height / 2.f, MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].getLocalBounds().height / 2.f, y);

								MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].setPosition(x, y);
								CreateMenuButtons(window);
								DisplayShapes(window);
							}
							if (Keyboard::isKeyPressed(Keyboard::Q) && !isPressed) //q pentru cresterea in size
							{
								isPressed = true;
								window.clear(MyColor::backgroundColor);

								unsigned int sizeX = MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].getSize().x + 20;
								unsigned int sizeY = MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].getSize().y + 20;

								if (sizeX >= width - 300 || sizeY >= width - 300) //acest if ne asigura ca nu dam resize cand height sau width este maxim,astfel evitam sa cream din dreptunghi patrat
								{
									isPressed = false;
									break;
								}

								Clamp(width - 300, 10, sizeX);
								Clamp(height - 300, 10, sizeY);

								MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].setSize(Vector2f(sizeX, sizeY));
								MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].setOrigin(MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].getLocalBounds().width / 2.f, MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].getLocalBounds().height / 2.f);

								CreateMenuButtons(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							if (Keyboard::isKeyPressed(Keyboard::E) && !isPressed) //e pentru scaderea in size
							{
								isPressed = true;
								window.clear(MyColor::backgroundColor);

								unsigned int sizeX = MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].getSize().x - 20;
								unsigned int sizeY = MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].getSize().y - 20;

								if (sizeX <= 20 || sizeY <= 20) //acest if ne asigura ca nu dam resize cand height sau width este minim,astfel evitam sa cream din dreptunghi patrat
								{
									isPressed = false;
									break;
								}

								if (sizeX > width * 10) //e ceva bug in care size=0 ajunge la size=400000?
									sizeX = 20;
								if (sizeY > height * 10)
									sizeY = 20;

								Clamp(width - 300, 20, sizeX);
								Clamp(height - 300, 20, sizeY);

								MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].setSize(Vector2f(sizeX, sizeY));
								MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].setOrigin(MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].getLocalBounds().width / 2.f, MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].getLocalBounds().height / 2.f);

								CreateMenuButtons(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							if (Keyboard::isKeyPressed(Keyboard::R) && !isPressed) //r pentru rotatia acelor de ceasornic
							{
								isPressed = true;
								window.clear(MyColor::backgroundColor);

								unsigned int angle = MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].getRotation() + 10;

								MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].setRotation(angle);

								MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].setOrigin(MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].getLocalBounds().width / 2.f, MyShapeSelector::shapes.rectangles[MyShapeSelector::shapes.rectangleCount - 1].getLocalBounds().height / 2.f);

								CreateMenuButtons(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							break;
						}
						case MyShapeType::Circle: {
							if (Mouse::isButtonPressed(Mouse::Left))
							{
								window.clear(MyColor::backgroundColor);

								unsigned int x = Mouse::getPosition(window).x;
								unsigned int y = Mouse::getPosition(window).y;

								if (x > width * 10) //e ceva bug in care din stanga se teleporteaza in dreapta?
									x = 0;
								if (y > height * 10)
									y = 0;

								Clamp(width - MyShapeSelector::shapes.circles[MyShapeSelector::shapes.circleCount - 1].getGlobalBounds().width + MyShapeSelector::shapes.circles[MyShapeSelector::shapes.circleCount - 1].getLocalBounds().width / 2.f, MyShapeSelector::shapes.circles[MyShapeSelector::shapes.circleCount - 1].getLocalBounds().width / 2.f, x);
								Clamp(height - 200 - MyShapeSelector::shapes.circles[MyShapeSelector::shapes.circleCount - 1].getGlobalBounds().height + MyShapeSelector::shapes.circles[MyShapeSelector::shapes.circleCount - 1].getLocalBounds().height / 2.f, MyShapeSelector::shapes.circles[MyShapeSelector::shapes.circleCount - 1].getLocalBounds().height / 2.f, y);

								MyShapeSelector::shapes.circles[MyShapeSelector::shapes.circleCount - 1].setPosition(x, y);
								CreateMenuButtons(window);
								DisplayShapes(window);
							}
							if (Keyboard::isKeyPressed(Keyboard::Q) && !isPressed) //q pentru cresterea in size
							{
								isPressed = true;
								window.clear(MyColor::backgroundColor);

								unsigned int r = MyShapeSelector::shapes.circles[MyShapeSelector::shapes.circleCount - 1].getRadius() + 20;

								Clamp(width / 3, 20, r);

								MyShapeSelector::shapes.circles[MyShapeSelector::shapes.circleCount - 1].setRadius(r);
								MyShapeSelector::shapes.circles[MyShapeSelector::shapes.circleCount - 1].setOrigin(r, r);

								CreateMenuButtons(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							if (Keyboard::isKeyPressed(Keyboard::E) && !isPressed) //e pentru scaderea in size
							{
								isPressed = true;
								window.clear(MyColor::backgroundColor);

								unsigned int r = MyShapeSelector::shapes.circles[MyShapeSelector::shapes.circleCount - 1].getRadius() - 20;

								if (r > height * 10)
									r = 20;

								Clamp(width / 3, 20, r);

								MyShapeSelector::shapes.circles[MyShapeSelector::shapes.circleCount - 1].setRadius(r);
								MyShapeSelector::shapes.circles[MyShapeSelector::shapes.circleCount - 1].setOrigin(r, r);

								CreateMenuButtons(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							//presupun ca nu trebuie sa punem optiunea de a roti un cerc,nu?

							break;
						}
						case MyShapeType::Triangle: {
							if (Mouse::isButtonPressed(Mouse::Left))
							{
								window.clear(MyColor::backgroundColor);

								unsigned int x = Mouse::getPosition(window).x;
								unsigned int y = Mouse::getPosition(window).y;

								if (x > width * 10) //e ceva bug in care din stanga se teleporteaza in dreapta?
									x = 0;
								if (y > height * 10)
									y = 0;

								Clamp(width - MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].getGlobalBounds().width + MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].getLocalBounds().width / 2.f, MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].getLocalBounds().width / 2.f, x);
								Clamp(height - 200 - MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].getGlobalBounds().height + MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].getLocalBounds().height / 2.f, MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].getLocalBounds().height / 2.f, y);

								MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].setPosition(x, y);
								CreateMenuButtons(window);
								DisplayShapes(window);
							}
							if (Keyboard::isKeyPressed(Keyboard::Q) && !isPressed) //q pentru cresterea in size
							{
								isPressed = true;
								window.clear(MyColor::backgroundColor);

								unsigned int r = MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].getRadius() + 20;

								Clamp(width / 3, 20, r);

								MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].setRadius(r);
								MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].setOrigin(r, r);

								CreateMenuButtons(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							if (Keyboard::isKeyPressed(Keyboard::E) && !isPressed) //e pentru scaderea in size
							{
								isPressed = true;
								window.clear(MyColor::backgroundColor);

								unsigned int r = MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].getRadius() - 20;

								if (r > height * 10)
									r = 20;

								Clamp(width / 3, 20, r);

								MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].setRadius(r);
								MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].setOrigin(r, r);

								CreateMenuButtons(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							if (Keyboard::isKeyPressed(Keyboard::R) && !isPressed) //r pentru rotatia acelor de ceasornic
							{
								isPressed = true;
								window.clear(MyColor::backgroundColor);

								unsigned int angle = MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].getRotation() + 10;
								unsigned int r = MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].getRadius();

								MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].setOrigin(r, r);
								MyShapeSelector::shapes.triangles[MyShapeSelector::shapes.triangleCount - 1].setRotation(angle);

								CreateMenuButtons(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}

							break;
						}
						default:
							break;
					}
					if (Keyboard::isKeyPressed(Keyboard::Escape) && !isPressed)
					{
						isPressed = true;

						Menu(window);

						isPressed = exitTimer();
					}
					break;
				}

				default:
					break;
			}
		}
		window.draw(playerText);
	}
	return 0;
}