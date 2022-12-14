namespace my
{
class SecondImage
{
public:
	static void initialize();
	static void display(sf::RenderWindow& window);
	static void handleEvents(sf::RenderWindow& window, sf::Event& event);
	static void displayText(sf::RenderWindow& window);
	static void moveAllShapes(sf::RenderWindow& window);
	static void movePointsFromPolygon(sf::RenderWindow& window);
};
}