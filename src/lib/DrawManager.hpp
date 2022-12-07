namespace my
{
class DrawManager
{
private:
	static void moveShape(sf::RenderWindow& window, sf::Event& event);
	static void savePosition(sf::RenderWindow& window, sf::Event& event);

public:
	static void drawShapes(sf::RenderWindow& window);
	static void handleEvents(sf::RenderWindow& window, sf::Event& event);
};
}