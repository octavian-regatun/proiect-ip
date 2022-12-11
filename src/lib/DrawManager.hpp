namespace my
{
class DrawManager
{
private:
	static void handleAddPolygonPoint(sf::RenderWindow& window, sf::Event& event);
	static void handleMoveShape(sf::RenderWindow& window, sf::Event& event);
	static void handleSavePosition(sf::RenderWindow& window, sf::Event& event);
	static void handleSizeIncrease(sf::RenderWindow& window, sf::Event& event);
	static void handleSizeDecrease(sf::RenderWindow& window, sf::Event& event);
	static void clampShapeSize(sf::RectangleShape& shape);
	static void clampShapeSize(sf::CircleShape& shape);
	static void drawLinesBetweenPolygonPoints(sf::RenderWindow& window);
	static sf::Vector2u setShapeBoundaries(sf::RenderWindow& window, sf::FloatRect localBounds, sf::FloatRect globalBounds);
	static void handleRotation(sf::RenderWindow& window, sf::Event& event);

public:
	static void drawShapes(sf::RenderWindow& window);
	static void handleEvents(sf::RenderWindow& window, sf::Event& event);
};
}