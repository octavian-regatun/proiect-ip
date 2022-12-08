#include <SFML/Graphics.hpp>

namespace my
{
struct Shapes
{
	std::vector<sf::RectangleShape> rectangles;
	std::vector<sf::CircleShape> circles;
	std::vector<sf::CircleShape> triangles;
};

enum class ShapeType
{
	Nothing,
	Rectangle,
	Circle,
	Triangle
};

class ShapeSelector
{
private:
	static void handleRectangleSelection(sf::RenderWindow& window);
	static void handleCircleSelection(sf::RenderWindow& window);
	static void handleTriangleSelection(sf::RenderWindow& window);
	static void addRectangle(sf::RenderWindow& window, unsigned int width, unsigned int height);
	static void addCircle(sf::RenderWindow& window, unsigned int radius);
	static void addTriangle(sf::RenderWindow& window, unsigned int side);
	static void setMovingShape();

public:
	static Shapes shapes;
	static ShapeType selectedShape;
	static ShapeType movingShape;
	static void displayMenu(sf::RenderWindow& window);
	static void refreshShapesCount();
	static void handleShapeSelection(sf::RenderWindow& window);
};
}