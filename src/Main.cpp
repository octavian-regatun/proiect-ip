#include "lib/MyColor.hpp"
#include "lib/MyFont.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

const int SHAPECTR = 10; //va trebui sa folosim vectori de shape-uri deoarece cand cream un nou shape si dam update la window sa tinem minte shape-urile

//acestea sunt shape-urile cu care vom face morphing(more to be added in the future maybe?)
CircleShape circle[SHAPECTR];
RectangleShape rectangle[SHAPECTR];
CircleShape triangle[SHAPECTR]; //se poate transforma din cerc in triunghi deoarece nu avem clasa pt triunghi

//contoare de shape-uri
int rectCtr = 0;
int circleCtr = 0;
int triangleCtr = 0;

sf::String playerInput;
sf::Text playerText;

int menuCounter = 0; //0 for MainMenu, 1 for CreateMenu

class Button
{
private:
	RectangleShape button;
	Text text;

public:
	Button(RenderWindow& window, Color fillColor, int length, int height, int x, int y)
	{
		button.setSize(sf::Vector2f(length, height));
		button.setOrigin(length / 2, height / 2);
		button.setPosition(x, y);
		button.setFillColor(fillColor);
		window.draw(button);
	}

	void addText(RenderWindow& window, Color color, string txt, Font font, int chSize)
	{
		text.setString(txt);
		text.setFont(font);
		text.setFillColor(color);

		text.setCharacterSize(chSize);

		float xPos = (button.getPosition().x + button.getGlobalBounds().width / 10) - (text.getGlobalBounds().width / 1.6f);
		float yPos = (button.getPosition().y + button.getGlobalBounds().height / 10) - (text.getGlobalBounds().height / .9f);

		text.setPosition({ xPos, yPos });

		window.draw(text);
	}

	Text getText()
	{
		return text;
	}
	RectangleShape getButton()
	{
		return button;
	}
};

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
void RefreshCounterShapes();

void CreateMenuButtons(RenderWindow& window)
{
	int length = 150;
	int height = 50;

	Button rectButton(window, MyColor::buttonColor, length, height, 200, window.getSize().y - 100);
	rectButton.addText(window, MyColor::textColor, "RECTANGLE", MyFont::font, 24);
	Mbuttons[1].btns[0] = rectButton.getButton();
	Mbuttons[1].text[0] = rectButton.getText();

	Button circleButton(window, MyColor::buttonColor, length, height, 500, window.getSize().y - 100);
	circleButton.addText(window, MyColor::textColor, "CIRCLE   ", MyFont::font, 24); //sau mai exista susta de a pune spatii in plus ca sa se alinieze😎
	Mbuttons[1].btns[1] = circleButton.getButton();
	Mbuttons[1].text[1] = circleButton.getText();

	Button triangleButton(window, MyColor::buttonColor, length, height, 800, window.getSize().y - 100);
	triangleButton.addText(window, MyColor::textColor, "TRIANGLE", MyFont::font, 24);
	Mbuttons[1].btns[2] = triangleButton.getButton();
	Mbuttons[1].text[2] = triangleButton.getText();

	Mbuttons[1].counter = 3;
}
void RefreshCounterShapes()
{
	rectCtr = triangleCtr = circleCtr = 0;
}
void DisplayShapes(RenderWindow& window)
{
	for (int i = 0; i < rectCtr; i++)
		window.draw(rectangle[i]);
	for (int i = 0; i < circleCtr; i++)
		window.draw(circle[i]);
	for (int i = 0; i < triangleCtr; i++)
		window.draw(triangle[i]);

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
	RefreshCounterShapes();

	//background color
	window.clear(MyColor::backgroundColor);
	menuCounter = 0;

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

	Button createButton(window, MyColor::buttonColor, length, height, x, y);
	createButton.addText(window, MyColor::textColor, "CREATE IMAGE", MyFont::font, 24); //ca textul sa se incadreze in centrul butonului ar trebui sa schimbi valorile length,height sau chSize(24)

	Mbuttons[0].btns[0] = createButton.getButton();
	Mbuttons[0].text[0] = createButton.getText();
	Mbuttons[0].counter = 1;

	window.display();
}
void CreateImagesMenu(RenderWindow& window)
{
	window.clear(MyColor::backgroundColor);
	menuCounter = 1;

	CreateMenuButtons(window);

	window.display();
}
int main()
{
	// create the window
	unsigned int width = 1000;
	unsigned int height = 1000;

	sf::RenderWindow window(sf::VideoMode(width, height), "My bug");

	MyFont::load();

	Menu(window);

	bool isPressed = false;

	char shapeType = 'n';  // v-a trebui sa tinem cont ce shape construim(n de la null?)
	char moveObject = 'n'; //sa stim ce piesa miscam

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
			switch (menuCounter) //butoanele vor functiona in functie de meniul curent
			{
				case 0: {

					RectangleShape collider = Mbuttons[menuCounter].btns[0]; //butonul de createImage

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
					RectangleShape rectangleBtn = Mbuttons[menuCounter].btns[0];
					RectangleShape circleBtn = Mbuttons[menuCounter].btns[1];
					RectangleShape triangleBtn = Mbuttons[menuCounter].btns[2];

					if (isMousePressed(window, rectangleBtn))
					{
						shapeType = 'r';
					}
					else if (isMousePressed(window, circleBtn))
					{
						shapeType = 'c';
					}
					else if (isMousePressed(window, triangleBtn))
					{
						shapeType = 't';
					}

					switch (shapeType) //scuze pt atatea switch/if dar sincer nu stiu cum sa fac altcumva :)
					{
						case 'r': {

							unsigned int h, l;
							cout << "Inaltimea: ";
							cin >> h;
							cout << "Lungimea: ";
							cin >> l;
							//aici poti daca vrei sa intrebi ce culoare ar dori(doar o idee)

							Clamp(width - 300, 10, l);
							Clamp(height - 300, 10, h);

							CreateImagesMenu(window);
							rectCtr++;
							rectangle[rectCtr - 1].setSize(Vector2f(l, h));
							rectangle[rectCtr - 1].setOrigin(l / 2.f, h / 2.f);
							rectangle[rectCtr - 1].setPosition(width / 2.f, height / 2.f);

							window.draw(rectangle[rectCtr - 1]);
							window.display();

							moveObject = shapeType;
							shapeType = 'n'; //la final reinitializam shapeType cu n pentru a finaliza procesul de creare
							break;
						}
						case 'c': {

							unsigned int r;
							cout << "Raza: ";
							cin >> r;

							Clamp(width / 3, 10, r);

							CreateImagesMenu(window);

							circleCtr++;

							circle[circleCtr - 1].setRadius(r);
							circle[circleCtr - 1].setOrigin(r, r);
							circle[circleCtr - 1].setPosition(width / 2.f, height / 2.f);

							window.draw(circle[circleCtr - 1]);
							window.display();

							moveObject = shapeType;
							shapeType = 'n';
							break;
						}
						case 't': {
							unsigned int l;
							cout << "Latura: ";
							cin >> l;

							Clamp(width / 3, 10, l);

							CreateImagesMenu(window);

							triangleCtr++;
							triangle[triangleCtr - 1].setRadius(l);
							triangle[triangleCtr - 1].setPointCount(3);
							triangle[triangleCtr - 1].setOrigin(l, l);
							triangle[triangleCtr - 1].setPosition(width / 2.f, height / 2.f);

							window.draw(triangle[triangleCtr - 1]);
							window.display();

							moveObject = shapeType;
							shapeType = 'n';
							break;
						}

						default:
							break;
					}

					switch (moveObject) //aici se misca obiectul
					{
						case 'r': {
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
								Clamp(width - rectangle[rectCtr - 1].getGlobalBounds().width + rectangle[rectCtr - 1].getLocalBounds().width / 2.f, rectangle[rectCtr - 1].getLocalBounds().width / 2.f, x);
								Clamp(height - 200 - rectangle[rectCtr - 1].getGlobalBounds().height + rectangle[rectCtr - 1].getLocalBounds().height / 2.f, rectangle[rectCtr - 1].getLocalBounds().height / 2.f, y);

								rectangle[rectCtr - 1].setPosition(x, y);
								CreateMenuButtons(window);
								DisplayShapes(window);
							}
							if (Keyboard::isKeyPressed(Keyboard::Q) && !isPressed) //q pentru cresterea in size
							{
								isPressed = true;
								window.clear(MyColor::backgroundColor);

								unsigned int sizeX = rectangle[rectCtr - 1].getSize().x + 20;
								unsigned int sizeY = rectangle[rectCtr - 1].getSize().y + 20;

								if (sizeX >= width - 300 || sizeY >= width - 300) //acest if ne asigura ca nu dam resize cand height sau width este maxim,astfel evitam sa cream din dreptunghi patrat
								{
									isPressed = false;
									break;
								}

								Clamp(width - 300, 10, sizeX);
								Clamp(height - 300, 10, sizeY);

								rectangle[rectCtr - 1].setSize(Vector2f(sizeX, sizeY));
								rectangle[rectCtr - 1].setOrigin(rectangle[rectCtr - 1].getLocalBounds().width / 2.f, rectangle[rectCtr - 1].getLocalBounds().height / 2.f);

								CreateMenuButtons(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							if (Keyboard::isKeyPressed(Keyboard::E) && !isPressed) //e pentru scaderea in size
							{
								isPressed = true;
								window.clear(MyColor::backgroundColor);

								unsigned int sizeX = rectangle[rectCtr - 1].getSize().x - 20;
								unsigned int sizeY = rectangle[rectCtr - 1].getSize().y - 20;

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

								rectangle[rectCtr - 1].setSize(Vector2f(sizeX, sizeY));
								rectangle[rectCtr - 1].setOrigin(rectangle[rectCtr - 1].getLocalBounds().width / 2.f, rectangle[rectCtr - 1].getLocalBounds().height / 2.f);

								CreateMenuButtons(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							if (Keyboard::isKeyPressed(Keyboard::R) && !isPressed) //r pentru rotatia acelor de ceasornic
							{
								isPressed = true;
								window.clear(MyColor::backgroundColor);

								unsigned int angle = rectangle[rectCtr - 1].getRotation() + 10;

								rectangle[rectCtr - 1].setRotation(angle);

								rectangle[rectCtr - 1].setOrigin(rectangle[rectCtr - 1].getLocalBounds().width / 2.f, rectangle[rectCtr - 1].getLocalBounds().height / 2.f);

								CreateMenuButtons(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							break;
						}
						case 'c': {
							if (Mouse::isButtonPressed(Mouse::Left))
							{
								window.clear(MyColor::backgroundColor);

								unsigned int x = Mouse::getPosition(window).x;
								unsigned int y = Mouse::getPosition(window).y;

								if (x > width * 10) //e ceva bug in care din stanga se teleporteaza in dreapta?
									x = 0;
								if (y > height * 10)
									y = 0;

								Clamp(width - circle[circleCtr - 1].getGlobalBounds().width + circle[circleCtr - 1].getLocalBounds().width / 2.f, circle[circleCtr - 1].getLocalBounds().width / 2.f, x);
								Clamp(height - 200 - circle[circleCtr - 1].getGlobalBounds().height + circle[circleCtr - 1].getLocalBounds().height / 2.f, circle[circleCtr - 1].getLocalBounds().height / 2.f, y);

								circle[circleCtr - 1].setPosition(x, y);
								CreateMenuButtons(window);
								DisplayShapes(window);
							}
							if (Keyboard::isKeyPressed(Keyboard::Q) && !isPressed) //q pentru cresterea in size
							{
								isPressed = true;
								window.clear(MyColor::backgroundColor);

								unsigned int r = circle[circleCtr - 1].getRadius() + 20;

								Clamp(width / 3, 20, r);

								circle[circleCtr - 1].setRadius(r);
								circle[circleCtr - 1].setOrigin(r, r);

								CreateMenuButtons(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							if (Keyboard::isKeyPressed(Keyboard::E) && !isPressed) //e pentru scaderea in size
							{
								isPressed = true;
								window.clear(MyColor::backgroundColor);

								unsigned int r = circle[circleCtr - 1].getRadius() - 20;

								if (r > height * 10)
									r = 20;

								Clamp(width / 3, 20, r);

								circle[circleCtr - 1].setRadius(r);
								circle[circleCtr - 1].setOrigin(r, r);

								CreateMenuButtons(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							//presupun ca nu trebuie sa punem optiunea de a roti un cerc,nu?

							break;
						}
						case 't': {
							if (Mouse::isButtonPressed(Mouse::Left))
							{
								window.clear(MyColor::backgroundColor);

								unsigned int x = Mouse::getPosition(window).x;
								unsigned int y = Mouse::getPosition(window).y;

								if (x > width * 10) //e ceva bug in care din stanga se teleporteaza in dreapta?
									x = 0;
								if (y > height * 10)
									y = 0;

								Clamp(width - triangle[triangleCtr - 1].getGlobalBounds().width + triangle[triangleCtr - 1].getLocalBounds().width / 2.f, triangle[triangleCtr - 1].getLocalBounds().width / 2.f, x);
								Clamp(height - 200 - triangle[triangleCtr - 1].getGlobalBounds().height + triangle[triangleCtr - 1].getLocalBounds().height / 2.f, triangle[triangleCtr - 1].getLocalBounds().height / 2.f, y);

								triangle[triangleCtr - 1].setPosition(x, y);
								CreateMenuButtons(window);
								DisplayShapes(window);
							}
							if (Keyboard::isKeyPressed(Keyboard::Q) && !isPressed) //q pentru cresterea in size
							{
								isPressed = true;
								window.clear(MyColor::backgroundColor);

								unsigned int r = triangle[triangleCtr - 1].getRadius() + 20;

								Clamp(width / 3, 20, r);

								triangle[triangleCtr - 1].setRadius(r);
								triangle[triangleCtr - 1].setOrigin(r, r);

								CreateMenuButtons(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							if (Keyboard::isKeyPressed(Keyboard::E) && !isPressed) //e pentru scaderea in size
							{
								isPressed = true;
								window.clear(MyColor::backgroundColor);

								unsigned int r = triangle[triangleCtr - 1].getRadius() - 20;

								if (r > height * 10)
									r = 20;

								Clamp(width / 3, 20, r);

								triangle[triangleCtr - 1].setRadius(r);
								triangle[triangleCtr - 1].setOrigin(r, r);

								CreateMenuButtons(window);
								DisplayShapes(window);

								isPressed = exitTimer();
							}
							if (Keyboard::isKeyPressed(Keyboard::R) && !isPressed) //r pentru rotatia acelor de ceasornic
							{
								isPressed = true;
								window.clear(MyColor::backgroundColor);

								unsigned int angle = triangle[triangleCtr - 1].getRotation() + 10;
								unsigned int r = triangle[triangleCtr - 1].getRadius();

								triangle[triangleCtr - 1].setOrigin(r, r);
								triangle[triangleCtr - 1].setRotation(angle);

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