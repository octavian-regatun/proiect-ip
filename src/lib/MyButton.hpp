#include <SFML/Graphics.hpp>

class MyButton
{
public:
	sf::RectangleShape button;
	sf::Text text;
	MyButton(sf::RenderWindow& window, sf::Color fillColor, int length, int height, int x, int y);
	void setText(sf::RenderWindow& window, sf::Color color, std::string txt, sf::Font font, int chSize);
	void onClick(sf::RenderWindow& window, sf::Event& ev, std::function<void()> func);
};
