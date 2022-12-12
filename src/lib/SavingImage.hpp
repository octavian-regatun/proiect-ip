//L FOR LOADING IMAGE, ENTER TO SAVE CURRENT SHAPE(LOADING WORKS WHEN IMAGE HAS NO SHAPE DRAWN)
//DRAWING ANY SHAPE WILL DELETE THE SAVED ONE

namespace my
{
struct Rectangle
{
	float length, height, posX, posY, rotation;
	int r, g, b;
};
struct Circle
{
	float posX, posY, rotation;
	int radius, r, g, b, pointCount;
};
struct thisPolygon
{
	int pointCounter, posX[10], posY[10]; // din pacate nu putem stoca std::vectori in fisiere binare 😞
};

class SavingImage
{
private:
	static void saveRectangle();
	static void saveCircle();
	static void loadRectangle(sf::RenderWindow& window);
	static void loadCircle(sf::RenderWindow& window);
	static void loadPolygon(sf::RenderWindow& window);

public:
	static void savePolygon();
	static void saveAllShapes();

	static void loadAllShapes(sf::RenderWindow& window);

	static Rectangle savingRect;
	static Circle savingCircle;
	static thisPolygon savingPolygon;
};

}