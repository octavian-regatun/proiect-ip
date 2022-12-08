namespace my
{
class DrawManager
{
private:
	static void handleMoveShape(sf::RenderWindow& window, sf::Event& event);
	static void handleSavePosition(sf::RenderWindow& window, sf::Event& event);
	static void handleSizeIncrease(sf::RenderWindow& window, sf::Event& event);
	static void handleSizeDecrease(sf::RenderWindow& window, sf::Event& event);
	static void clampShapeSize(sf::RectangleShape& shape);
	static void clampShapeSize(sf::CircleShape& shape);
	// static void restrictShapePosition

public:
	static void drawShapes(sf::RenderWindow& window);
	static void handleEvents(sf::RenderWindow& window, sf::Event& event);
};
}