#include "lib/AllButtons.hpp"
#include "lib/Button.hpp"
#include "lib/Color.hpp"
#include "lib/Font.hpp"
#include "lib/Screen.hpp"
#include "lib/ShapeSelector.hpp"
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
void CreateImagesMenu(RenderWindow& window);
void Menu(RenderWindow& window);
bool isMousePressed(RenderWindow& window, RectangleShape collider);
bool exitTimer(); //avem nevoie de timer deoarece cand dam esc si nu avem timer se va apela de mai multe ori exit-ul
void Clamp(unsigned int max, unsigned int min, unsigned int& value);
void DisplayShapes(RenderWindow& window);

void DisplayShapes(RenderWindow& window)
{
	for (int i = 0; i < my::ShapeSelector::shapes.rectanglesCount; i++)
		window.draw(my::ShapeSelector::shapes.rectangles[i]);
	for (int i = 0; i < my::ShapeSelector::shapes.circlesCount; i++)
		window.draw(my::ShapeSelector::shapes.circles[i]);
	for (int i = 0; i < my::ShapeSelector::shapes.trianglesCount; i++)
		window.draw(my::ShapeSelector::shapes.triangles[i]);

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
	my::ShapeSelector::refreshShapesCount();

	//background color
	window.clear(my::Color::backgroundColor);
	my::Screen::goToScreen(my::ScreenType::Start);

	int x = window.getSize().x / 2.f;
	int y = window.getSize().y / 2.f;

	//Title
	Text title;

	title.setString("MENU");
	title.setFont(my::Font::fontBold);
	title.setCharacterSize(70);
	title.setPosition(x - 100, 100);
	title.setFillColor(my::Color::textColor);
	window.draw(title);

	//button for create feature
	int length = 200;
	int height = 50;

	my::Button createButton(window, my::Color::buttonColor, length, height, x, y);
	createButton.setText(window, my::Color::textColor, "CREATE IMAGE", my::Font::font, 24); //ca textul sa se incadreze in centrul butonului ar trebui sa schimbi valorile length,height sau chSize(24)

	Mbuttons[0].btns[0] = createButton.button;
	Mbuttons[0].text[0] = createButton.text;
	Mbuttons[0].counter = 1;

	window.display();
}
void CreateImagesMenu(RenderWindow& window)
{
	window.clear(my::Color::backgroundColor);
	my::Screen::goToScreen(my::ScreenType::FirstImage);

	my::ShapeSelector::displayMenu(window);

	window.display();
}
int main()
{
	unsigned int width = 1000;
	unsigned int height = 1000;

	sf::RenderWindow window(sf::VideoMode(width, height), "Morphing - Proiect IP");

	my::Font::load();

	Menu(window);

	bool isPressed = false;

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			my::AllButtons::handleEvents(window, event);
			// "close requested" event: we close the window
			switch (event.type)
			{
				case Event::Closed:
					window.close();
					break;

				default:
					break;
			}

			switch (my::Screen::currentScreen) //butoanele vor functiona in functie de meniul curent
			{
				case my::ScreenType::Start: {

					RectangleShape collider = Mbuttons[my::Screen::currentScreen].btns[0]; //butonul de createImage

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
				case my::ScreenType::FirstImage: {
					RectangleShape rectangleBtn = Mbuttons[my::Screen::currentScreen].btns[0];
					RectangleShape circleBtn = Mbuttons[my::Screen::currentScreen].btns[1];
					RectangleShape triangleBtn = Mbuttons[my::Screen::currentScreen].btns[2];

					if (isMousePressed(window, rectangleBtn))
					{
						my::ShapeSelector::selectedShape = my::ShapeType::Rectangle;
					}
					else if (isMousePressed(window, circleBtn))
					{
						my::ShapeSelector::selectedShape = my::ShapeType::Circle;
					}
					else if (isMousePressed(window, triangleBtn))
					{
						my::ShapeSelector::selectedShape = my::ShapeType::Triangle;
					}

					switch (my::ShapeSelector::selectedShape) //scuze pt atatea switch/if dar sincer nu stiu cum sa fac altcumva :)
					{
						case my::ShapeType::Rectangle: {

							unsigned int h, l;
							cout << "Inaltimea: ";
							cin >> h;
							cout << "Lungimea: ";
							cin >> l;
							//aici poti daca vrei sa intrebi ce culoare ar dori(doar o idee)

							Clamp(width - 300, 10, l);
							Clamp(height - 300, 10, h);

							CreateImagesMenu(window);
							my::ShapeSelector::shapes.rectanglesCount++;
							my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].setSize(Vector2f(l, h));
							my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].setOrigin(l / 2.f, h / 2.f);
							my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].setPosition(width / 2.f, height / 2.f);

							window.draw(my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1]);
							window.display();

							my::ShapeSelector::currentMovingShape = my::ShapeSelector::selectedShape;
							my::ShapeSelector::selectedShape = my::ShapeType::Nothing; //la final reinitializam shapeType cu n pentru a finaliza procesul de creare
							break;
						}
						case my::ShapeType::Circle: {

							unsigned int r;
							cout << "Raza: ";
							cin >> r;

							Clamp(width / 3, 10, r);

							CreateImagesMenu(window);

							my::ShapeSelector::shapes.circlesCount++;

							my::ShapeSelector::shapes.circles[my::ShapeSelector::shapes.circlesCount - 1].setRadius(r);
							my::ShapeSelector::shapes.circles[my::ShapeSelector::shapes.circlesCount - 1].setOrigin(r, r);
							my::ShapeSelector::shapes.circles[my::ShapeSelector::shapes.circlesCount - 1].setPosition(width / 2.f, height / 2.f);

							window.draw(my::ShapeSelector::shapes.circles[my::ShapeSelector::shapes.circlesCount - 1]);
							window.display();

							my::ShapeSelector::currentMovingShape = my::ShapeSelector::selectedShape;
							my::ShapeSelector::selectedShape = my::ShapeType::Nothing;
							break;
						}
						case my::ShapeType::Triangle: {
							unsigned int l;
							cout << "Latura: ";
							cin >> l;

							Clamp(width / 3, 10, l);

							CreateImagesMenu(window);

							my::ShapeSelector::shapes.trianglesCount++;
							my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].setRadius(l);
							my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].setPointCount(3);
							my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].setOrigin(l, l);
							my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].setPosition(width / 2.f, height / 2.f);

							window.draw(my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.circlesCount - 1]);
							window.display();

							my::ShapeSelector::currentMovingShape = my::ShapeSelector::selectedShape;
							my::ShapeSelector::selectedShape = my::ShapeType::Nothing;
							break;
						}

						default:
							break;
					}

					switch (my::ShapeSelector::currentMovingShape) //aici se misca obiectul
					{
						case my::ShapeType::Rectangle: {
							if (Mouse::isButtonPressed(Mouse::Left))
							{
								window.clear(my::Color::backgroundColor);

								unsigned int x = Mouse::getPosition(window).x;
								unsigned int y = Mouse::getPosition(window).y;

								if (x > width * 10) //e ceva bug in care din stanga se teleporteaza in dreapta?
									x = 0;
								if (y > height * 10)
									y = 0;

								//limitele in care se poate misca obietul
								Clamp(width - my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].getGlobalBounds().width + my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].getLocalBounds().width / 2.f, my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].getLocalBounds().width / 2.f, x);
								Clamp(height - 200 - my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].getGlobalBounds().height + my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].getLocalBounds().height / 2.f, my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].getLocalBounds().height / 2.f, y);

								my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].setPosition(x, y);
								my::ShapeSelector::displayMenu(window);
								DisplayShapes(window);
							}
							if (Keyboard::isKeyPressed(Keyboard::Q) && !isPressed) //q pentru cresterea in size
							{
								isPressed = true;
								window.clear(my::Color::backgroundColor);

								unsigned int sizeX = my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].getSize().x + 20;
								unsigned int sizeY = my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].getSize().y + 20;

								if (sizeX >= width - 300 || sizeY >= width - 300) //acest if ne asigura ca nu dam resize cand height sau width este maxim,astfel evitam sa cream din dreptunghi patrat
								{
									isPressed = false;
									break;
								}

								Clamp(width - 300, 10, sizeX);
								Clamp(height - 300, 10, sizeY);

								my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].setSize(Vector2f(sizeX, sizeY));
								my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].setOrigin(my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].getLocalBounds().width / 2.f, my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].getLocalBounds().height / 2.f);

								my::ShapeSelector::displayMenu(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							if (Keyboard::isKeyPressed(Keyboard::E) && !isPressed) //e pentru scaderea in size
							{
								isPressed = true;
								window.clear(my::Color::backgroundColor);

								unsigned int sizeX = my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].getSize().x - 20;
								unsigned int sizeY = my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].getSize().y - 20;

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

								my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].setSize(Vector2f(sizeX, sizeY));
								my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].setOrigin(my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].getLocalBounds().width / 2.f, my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].getLocalBounds().height / 2.f);

								my::ShapeSelector::displayMenu(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							if (Keyboard::isKeyPressed(Keyboard::R) && !isPressed) //r pentru rotatia acelor de ceasornic
							{
								isPressed = true;
								window.clear(my::Color::backgroundColor);

								unsigned int angle = my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].getRotation() + 10;

								my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].setRotation(angle);

								my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].setOrigin(my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].getLocalBounds().width / 2.f, my::ShapeSelector::shapes.rectangles[my::ShapeSelector::shapes.rectanglesCount - 1].getLocalBounds().height / 2.f);

								my::ShapeSelector::displayMenu(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							break;
						}
						case my::ShapeType::Circle: {
							if (Mouse::isButtonPressed(Mouse::Left))
							{
								window.clear(my::Color::backgroundColor);

								unsigned int x = Mouse::getPosition(window).x;
								unsigned int y = Mouse::getPosition(window).y;

								if (x > width * 10) //e ceva bug in care din stanga se teleporteaza in dreapta?
									x = 0;
								if (y > height * 10)
									y = 0;

								Clamp(width - my::ShapeSelector::shapes.circles[my::ShapeSelector::shapes.circlesCount - 1].getGlobalBounds().width + my::ShapeSelector::shapes.circles[my::ShapeSelector::shapes.circlesCount - 1].getLocalBounds().width / 2.f, my::ShapeSelector::shapes.circles[my::ShapeSelector::shapes.circlesCount - 1].getLocalBounds().width / 2.f, x);
								Clamp(height - 200 - my::ShapeSelector::shapes.circles[my::ShapeSelector::shapes.circlesCount - 1].getGlobalBounds().height + my::ShapeSelector::shapes.circles[my::ShapeSelector::shapes.circlesCount - 1].getLocalBounds().height / 2.f, my::ShapeSelector::shapes.circles[my::ShapeSelector::shapes.circlesCount - 1].getLocalBounds().height / 2.f, y);

								my::ShapeSelector::shapes.circles[my::ShapeSelector::shapes.circlesCount - 1].setPosition(x, y);
								my::ShapeSelector::displayMenu(window);
								DisplayShapes(window);
							}
							if (Keyboard::isKeyPressed(Keyboard::Q) && !isPressed) //q pentru cresterea in size
							{
								isPressed = true;
								window.clear(my::Color::backgroundColor);

								unsigned int r = my::ShapeSelector::shapes.circles[my::ShapeSelector::shapes.circlesCount - 1].getRadius() + 20;

								Clamp(width / 3, 20, r);

								my::ShapeSelector::shapes.circles[my::ShapeSelector::shapes.circlesCount - 1].setRadius(r);
								my::ShapeSelector::shapes.circles[my::ShapeSelector::shapes.circlesCount - 1].setOrigin(r, r);

								my::ShapeSelector::displayMenu(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							if (Keyboard::isKeyPressed(Keyboard::E) && !isPressed) //e pentru scaderea in size
							{
								isPressed = true;
								window.clear(my::Color::backgroundColor);

								unsigned int r = my::ShapeSelector::shapes.circles[my::ShapeSelector::shapes.circlesCount - 1].getRadius() - 20;

								if (r > height * 10)
									r = 20;

								Clamp(width / 3, 20, r);

								my::ShapeSelector::shapes.circles[my::ShapeSelector::shapes.circlesCount - 1].setRadius(r);
								my::ShapeSelector::shapes.circles[my::ShapeSelector::shapes.circlesCount - 1].setOrigin(r, r);

								my::ShapeSelector::displayMenu(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							//presupun ca nu trebuie sa punem optiunea de a roti un cerc,nu?

							break;
						}
						case my::ShapeType::Triangle: {
							if (Mouse::isButtonPressed(Mouse::Left))
							{
								window.clear(my::Color::backgroundColor);

								unsigned int x = Mouse::getPosition(window).x;
								unsigned int y = Mouse::getPosition(window).y;

								if (x > width * 10) //e ceva bug in care din stanga se teleporteaza in dreapta?
									x = 0;
								if (y > height * 10)
									y = 0;

								Clamp(width - my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].getGlobalBounds().width + my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].getLocalBounds().width / 2.f, my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].getLocalBounds().width / 2.f, x);
								Clamp(height - 200 - my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].getGlobalBounds().height + my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].getLocalBounds().height / 2.f, my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].getLocalBounds().height / 2.f, y);

								my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].setPosition(x, y);
								my::ShapeSelector::displayMenu(window);
								DisplayShapes(window);
							}
							if (Keyboard::isKeyPressed(Keyboard::Q) && !isPressed) //q pentru cresterea in size
							{
								isPressed = true;
								window.clear(my::Color::backgroundColor);

								unsigned int r = my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].getRadius() + 20;

								Clamp(width / 3, 20, r);

								my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].setRadius(r);
								my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].setOrigin(r, r);

								my::ShapeSelector::displayMenu(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							if (Keyboard::isKeyPressed(Keyboard::E) && !isPressed) //e pentru scaderea in size
							{
								isPressed = true;
								window.clear(my::Color::backgroundColor);

								unsigned int r = my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].getRadius() - 20;

								if (r > height * 10)
									r = 20;

								Clamp(width / 3, 20, r);

								my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].setRadius(r);
								my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].setOrigin(r, r);

								my::ShapeSelector::displayMenu(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							if (Keyboard::isKeyPressed(Keyboard::R) && !isPressed) //r pentru rotatia acelor de ceasornic
							{
								isPressed = true;
								window.clear(my::Color::backgroundColor);

								unsigned int angle = my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].getRotation() + 10;
								unsigned int r = my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].getRadius();

								my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].setOrigin(r, r);
								my::ShapeSelector::shapes.triangles[my::ShapeSelector::shapes.trianglesCount - 1].setRotation(angle);

								my::ShapeSelector::displayMenu(window);
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