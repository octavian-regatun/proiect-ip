#include <SFML/Graphics.hpp>

namespace my
{
struct Shapes
{
	//contoare de shape-uri
	int rectanglesCount, circlesCount, trianglesCount;
	//acestea sunt shape-urile cu care vom face morphing(more to be added in the future maybe?)
	sf::RectangleShape* rectangles;
	sf::CircleShape* circles;
	//se poate transforma din cerc in triunghi deoarece nu avem clasa pt triunghi
	sf::CircleShape* triangles;
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
public:
	static Shapes shapes;
	static ShapeType selectedShape;
	// sa stim ce piesa miscam
	static ShapeType currentMovingShape;
	static void displayMenu(sf::RenderWindow& window);
	static void refreshShapesCount();
};
}