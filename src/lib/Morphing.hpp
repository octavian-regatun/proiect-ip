namespace my
{
class Morphing
{
public:
	static void displayMorphingButton(sf::RenderWindow& window);
	static void animateAllShapes(sf::RenderWindow& window, unsigned int ms);
	static void animateCircle(sf::RenderWindow& window, sf::CircleShape& circle, sf::Vector2u finalPoint, float progress);
	static void animateRectangle(sf::RenderWindow& window, sf::RectangleShape& rectangle, sf::Vector2u finalPoint, float progress);
	static float lerp(float a, float b, float t);
};
}