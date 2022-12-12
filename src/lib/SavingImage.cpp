#include "SavingImage.hpp"
#include "ShapeSelector.hpp"
#include <fstream>
#include <iostream>

namespace my
{
Rectangle SavingImage::savingRect;
Circle SavingImage::savingCircle;
thisPolygon SavingImage::savingPolygon;

std::string rectFileName = "rectangle.dat";
std::string circleFileName = "circle.dat";
std::string polygonFileName = "polygon.dat";

void SavingImage::saveAllShapes()
{

	switch (ShapeSelector::movingShape)
	{
		case ShapeType::Rectangle:
			saveRectangle();
			break;
		case ShapeType::Circle:
			saveCircle();
			break;
		case ShapeType::Triangle:
			saveCircle();
			break;
		case ShapeType::Polygon:
			savePolygon();
			break;

		default:
			break;
	}
}
void SavingImage::loadAllShapes(sf::RenderWindow& window)
{
	static int ok = 0;
	if (ok != 0)
		return;
	ok = 1;

	loadRectangle(window);
	loadCircle(window);
	loadPolygon(window);
}

void SavingImage::saveRectangle()
{
	std::fstream f;
	if (ShapeSelector::shapes.rectangles.size() == 1)
		f.open(rectFileName, std::ios::out | std::ios::binary);
	else
		f.open(rectFileName, std::ios::app | std::ios::binary);

	auto& rect = ShapeSelector::shapes.rectangles.back();
	savingRect = { rect.getSize().x, rect.getSize().y, rect.getPosition().x, rect.getPosition().y, rect.getRotation(), rect.getFillColor().r, rect.getFillColor().g, rect.getFillColor().b }; //saving length,height,position and color

	if (!f.is_open())
	{
		std::cout << "ERROR SAVING " << rectFileName;
		return;
	}
	f.write(reinterpret_cast<char*>(&savingRect), sizeof(Rectangle));

	f.close();
}
void SavingImage::saveCircle()
{
	std::fstream f;
	if (ShapeSelector::shapes.circles.size() + ShapeSelector::shapes.triangles.size() <= 1)
		f.open(circleFileName, std::ios::out | std::ios::binary);
	else
		f.open(circleFileName, std::ios::app | std::ios::binary);

	sf::CircleShape circle;
	if (ShapeSelector::movingShape == ShapeType::Triangle)
	{
		circle = ShapeSelector::shapes.triangles.back();
		std::cout << "triunghi\n";
	}
	else
	{
		circle = ShapeSelector::shapes.circles.back();
		std::cout << "cerc\n";
	}

	savingCircle = { circle.getPosition().x, circle.getPosition().y, circle.getRotation(), circle.getRadius(), circle.getFillColor().r, circle.getFillColor().g, circle.getFillColor().b, circle.getPointCount() };
	if (!f.is_open())
	{
		std::cout << "ERROR SAVING " << circleFileName;
		return;
	}
	f.write(reinterpret_cast<char*>(&savingCircle), sizeof(Circle));

	f.close();
}
void SavingImage::savePolygon()
{
	std::fstream f;
	if (ShapeSelector::shapes.polygons.size() == 1)
		f.open(polygonFileName, std::ios::out | std::ios::binary);
	else
		f.open(polygonFileName, std::ios::app | std::ios::binary);

	auto& polygon = ShapeSelector::shapes.polygons.back();

	savingPolygon.pointCounter = polygon.points.size();
	f.write(reinterpret_cast<char*>(&savingPolygon.pointCounter), sizeof(savingPolygon.pointCounter));

	if (!f.is_open())
	{
		std::cout << "ERROR SAVING " << rectFileName;
		return;
	}
	for (int i = 0; i < savingPolygon.pointCounter; i++)
	{
		savingPolygon.posX[i] = polygon.points[i].getPosition().x;
		savingPolygon.posY[i] = polygon.points[i].getPosition().y;
		f.write(reinterpret_cast<char*>(&savingPolygon.posX[i]), sizeof(savingPolygon.posX[i]));
		f.write(reinterpret_cast<char*>(&savingPolygon.posY[i]), sizeof(savingPolygon.posY[i]));
	}

	f.close();
}

void SavingImage::loadRectangle(sf::RenderWindow& window)
{
	std::ifstream f;
	f.open(rectFileName, std::ios::in | std::ios::binary);

	int fileSize = 0;

	f.seekg(0, std::ios::end);
	fileSize = f.tellg();
	f.seekg(0, std::ios::beg);

	while (f.tellg() < fileSize)
	{
		Rectangle currRect;
		f.read(reinterpret_cast<char*>(&currRect), sizeof(currRect));

		sf::RectangleShape loadRect(sf::Vector2f(currRect.length, currRect.height));
		loadRect.setRotation(currRect.rotation);
		loadRect.setOrigin(sf::Vector2f(currRect.length / 2.f, currRect.height / 2.f));
		loadRect.setPosition(sf::Vector2f(currRect.posX, currRect.posY));
		loadRect.setFillColor(sf::Color(currRect.r, currRect.g, currRect.b));

		ShapeSelector::shapes.rectangles.push_back(loadRect);
	}

	f.close();
}
void SavingImage::loadCircle(sf::RenderWindow& window)
{
	std::ifstream f;
	f.open(circleFileName, std::ios::in | std::ios::binary);

	int fileSize = 0;

	f.seekg(0, std::ios::end);
	fileSize = f.tellg();
	f.seekg(0, std::ios::beg);

	while (f.tellg() < fileSize)
	{
		Circle currCircle;
		f.read(reinterpret_cast<char*>(&currCircle), sizeof(currCircle));

		sf::CircleShape newCircle(currCircle.radius);
		newCircle.setOrigin(currCircle.radius, currCircle.radius);
		newCircle.setRotation(currCircle.rotation);
		newCircle.setPosition(sf::Vector2f(currCircle.posX, currCircle.posY));
		newCircle.setPointCount(currCircle.pointCount);
		newCircle.setFillColor(sf::Color(currCircle.r, currCircle.g, currCircle.b));

		if (newCircle.getPointCount() == 3)
			ShapeSelector::shapes.triangles.push_back(newCircle);
		else
			ShapeSelector::shapes.circles.push_back(newCircle);
	}

	f.close();
}
void SavingImage::loadPolygon(sf::RenderWindow& window)
{
	std::ifstream f;
	f.open(polygonFileName, std::ios::in | std::ios::binary);

	int fileSize = 0;

	f.seekg(0, std::ios::end);
	fileSize = f.tellg();
	f.seekg(0, std::ios::beg);

	thisPolygon currPolygon;
	Polygon poly;

	while (f.tellg() < fileSize)
	{
		f.read(reinterpret_cast<char*>(&currPolygon.pointCounter), sizeof(currPolygon.pointCounter));
		poly.isFinished = true;
		for (int i = 0; i < currPolygon.pointCounter; i++)
		{
			f.read(reinterpret_cast<char*>(&currPolygon.posX[i]), sizeof(currPolygon.posX[i]));
			f.read(reinterpret_cast<char*>(&currPolygon.posY[i]), sizeof(currPolygon.posY[i]));

			poly.addPoint(window, { currPolygon.posX[i], currPolygon.posY[i] });
		}
		poly.drawLastLine(window);
		ShapeSelector::shapes.polygons.push_back(poly);
	}

	//	for (int i = 0; i < currPolygon.pointCounter; i++)
	//	{
	//		std::cout << currPolygon.posX[i] << ' ' << currPolygon.posY[i] << '\n';
	//	}
	f.close();
}
}
