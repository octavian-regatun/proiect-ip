namespace my
{
class SecondImage
{
private:
	static void saveSecondImage();

public:
	static void display(sf::RenderWindow& window);
	static void handleEvents(sf::RenderWindow& window, sf::Event& event);
	static void displayText(sf::RenderWindow& window);
	static void moveAllShapes(sf::RenderWindow& window);
	static void movePointsFromPolygon(sf::RenderWindow& window);
};
}