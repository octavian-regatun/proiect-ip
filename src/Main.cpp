#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;
//tricolorul aplicatiei(se poate schimba pe viitor daca ai o idee mai buna de paleta)
Color backgroundClr = Color(44, 62, 80);
Color btnClr = Color(22, 160, 133);
Color txtClr = Color(26, 188, 156);

Font font, fontBold;

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
void CreateImagesMenu(RenderWindow& window);
void Menu(RenderWindow& window);
bool isMousePressed(RenderWindow& window, RectangleShape collider);
bool exitTimer(); //avem nevoie de timer deoarece cand dam esc si nu avem timer se va apela de mai multe ori exit-ul

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
	//background color
	window.clear(backgroundClr);
	menuCounter = 0;

	int x = window.getSize().x / 2.f;
	int y = window.getSize().y / 2.f;

	//Title
	Text title;

	title.setString("MENU");
	title.setFont(fontBold);
	title.setCharacterSize(70);
	title.setPosition(x - 100, 100);
	title.setFillColor(txtClr);
	window.draw(title);

	//button for create feature
	int length = 200;
	int height = 50;

	Button createButton(window, btnClr, length, height, x, y);
	createButton.addText(window, txtClr, "CREATE IMAGE", font, 24); //ca textul sa se incadreze in centrul butonului ar trebui sa schimbi valorile length,height sau chSize(24)

	Mbuttons[0].btns[0] = createButton.getButton();
	Mbuttons[0].text[0] = createButton.getText();
	Mbuttons[0].counter = 1;

	window.display();
}
void CreateImagesMenu(RenderWindow& window)
{
	window.clear(backgroundClr);
	menuCounter = 1;
	int length = 150;
	int height = 50;

	Button rectButton(window, btnClr, length, height, 200, 900);
	rectButton.addText(window, txtClr, "RECTANGLE", font, 24);
	Mbuttons[1].btns[0] = rectButton.getButton();
	Mbuttons[1].text[0] = rectButton.getText();

	Button circleButton(window, btnClr, length, height, 500, 900);
	circleButton.addText(window, txtClr, "CIRCLE   ", font, 24); //sau mai exista susta de a pune spatii in plus ca sa se alinieze😎
	Mbuttons[1].btns[1] = circleButton.getButton();
	Mbuttons[1].text[1] = circleButton.getText();

	Button triangleButton(window, btnClr, length, height, 800, 900);
	triangleButton.addText(window, txtClr, "TRIANGLE", font, 24);
	Mbuttons[1].btns[2] = triangleButton.getButton();
	Mbuttons[1].text[2] = triangleButton.getText();

	Mbuttons[1].counter = 3;

	window.display();
}
int main()
{
	// create the window
	int width = 1000;
	int height = 1000;

	sf::RenderWindow window(sf::VideoMode(width, height), "My bug");

	if (!font.loadFromFile("DIN.ttf"))
		cout << "ERROR, DIN FONT NOT LOADED";

	if (!fontBold.loadFromFile("DINBold.ttf"))
		cout << "ERROR, DINBold FONT NOT LOADED";

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
			if (event.type == Event::Closed)
				window.close();
			else
				switch (menuCounter) //butoanele vor functiona in functie de meniul curent
				{
					case 0: {

						RectangleShape collider = Mbuttons[menuCounter].btns[0];
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
						RectangleShape rectangle = Mbuttons[menuCounter].btns[0];
						RectangleShape circle = Mbuttons[menuCounter].btns[1];
						RectangleShape triangle = Mbuttons[menuCounter].btns[2];

						if (isMousePressed(window, rectangle))
						{
							CreateImagesMenu(window);
							int rectLength = 120;
							int rectHeight = 50;
							RectangleShape rectShape(Vector2f(rectLength, rectHeight));
							rectShape.setOrigin(rectLength / 2.f, rectHeight / 2.f);
							rectShape.setPosition(width / 2.f, height / 2.f);

							window.draw(rectShape);
							window.display();
						}
						else if (isMousePressed(window, circle))
						{
							CreateImagesMenu(window);

							CircleShape circle(50);
							circle.setOrigin(50, 50);
							circle.setPosition(100, 100);

							window.draw(circle);
							window.display();
						}
						else if (isMousePressed(window, triangle))
						{
							CreateImagesMenu(window);

							CircleShape triangle(80.f, 3);
							triangle.setOrigin(50, 50);
							triangle.setPosition(400, 200);

							window.draw(triangle);
							window.display();
						}
						else if (Keyboard::isKeyPressed(Keyboard::Escape) && !isPressed)
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
	}
	return 0;
}