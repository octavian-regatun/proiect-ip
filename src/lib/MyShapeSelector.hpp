// #include <SFML/Graphics.hpp>

struct MyShapes
{
	//contoare de shape-uri
	int rectangleCount, circleCount, triangleCount;
	//acestea sunt shape-urile cu care vom face morphing(more to be added in the future maybe?)
	sf::RectangleShape* rectangles;
	sf::CircleShape* circles;
	//se poate transforma din cerc in triunghi deoarece nu avem clasa pt triunghi
	sf::CircleShape* triangles;
};

enum class MyShapeType
{
	Nothing,
	Rectangle,
	Circle,
	Triangle
};

class MyShapeSelector
{
public:
	static MyShapes shapes;
	static MyShapeType selectedShape;
	//sa stim ce piesa miscam
	static MyShapeType currentMovingShape;
	static void display(sf::RenderWindow& window);
	static void refreshShapesCount();
};