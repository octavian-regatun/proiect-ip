#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;
CircleShape createCircle(int r, float x, float y, Color color);

void modifyCircle(CircleShape& circle, int step, RenderWindow& window);

CircleShape createCircle(int r, float x, float y, Color color)
{
	CircleShape circle(r);
	circle.setOrigin(r, r);
	circle.setFillColor(color);
	circle.setPosition(x, y);

	circle.setPointCount(30);

	return circle;
}
void modifyCircle(CircleShape& circle, int step, RenderWindow& window)
{
	int r = circle.getRadius();

	circle.setPointCount(step);
	circle.setRadius(--r);
	window.draw(circle);
}
int main()
{
	// create the window
	int width = 1000;
	int height = 1000;
	sf::RenderWindow window(sf::VideoMode(width, height), "My bug");
	int ok = 0;
	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (ok == 0)
		{
			int r = 100;

			CircleShape face, mouth;

			face = createCircle(r, (window.getSize().x / 2.f), (window.getSize().y / 2.f), Color(141, 85, 36));
			mouth = createCircle(r / 2, (window.getSize().x / 2.f), (window.getSize().y / 2.f) + 35, Color(255, 0, 0));

			window.draw(face);
			window.draw(mouth);
			window.display();

			Time t1 = seconds(.25f);

			unsigned int k = 30;

			for (int i = k; i >= 4; i--)
			{
				Clock clock;
				Time elapsedTime = clock.getElapsedTime();

				while (t1 > elapsedTime) //timer goes brrr
					elapsedTime = clock.getElapsedTime();

				window.clear(sf::Color::Black);

				modifyCircle(face, i, window);
				modifyCircle(mouth, i, window);
				window.display();
			}
			window.clear(sf::Color::Black);
			r = face.getRadius();

			face.setRotation(45);
			window.draw(face);

			mouth.setRotation(45);
			window.draw(mouth);

			window.display();

			ok = 1;
		}
	}
}
