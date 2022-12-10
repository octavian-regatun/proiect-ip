#include "DrawManager.hpp"
#include "Clamp.hpp"
#include "ShapeSelector.hpp"

namespace my
{
void DrawManager::drawShapes(sf::RenderWindow& window)
{
	for (auto& rectangle : ShapeSelector::shapes.rectangles)
	{
		window.draw(rectangle);
	}

	for (auto& circle : ShapeSelector::shapes.circles)
	{
		window.draw(circle);
	}

	for (auto& triangle : ShapeSelector::shapes.triangles)
	{
		window.draw(triangle);
	}

	for (auto& polygon : ShapeSelector::shapes.polygons)
	{
		for (auto& point : polygon.points)
		{
			window.draw(point);
			window.display();
		}
	}

	drawLinesBetweenPolygonPoints(window);
}

void DrawManager::handleEvents(sf::RenderWindow& window, sf::Event& event)
{
	handleMoveShape(window, event);
	handleSavePosition(window, event);
	handleSizeIncrease(window, event);
	handleSizeDecrease(window, event);
}

void DrawManager::handleMoveShape(sf::RenderWindow& window, sf::Event& event)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		switch (ShapeSelector::movingShape)
		{
			case ShapeType::Rectangle:
				ShapeSelector::shapes.rectangles.back().setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				break;
			case ShapeType::Circle:
				ShapeSelector::shapes.circles.back().setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				break;
			case ShapeType::Triangle:
				ShapeSelector::shapes.triangles.back().setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				break;
			case ShapeType::Polygon:
				handleAddPolygonPoint(window, event);
				break;
			case ShapeType::Nothing:
				break;
			default:
				break;
		}
}

void DrawManager::handleAddPolygonPoint(sf::RenderWindow& window, sf::Event& event)
{

	if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
	{
		sf::CircleShape point;

		point.setRadius(5);
		point.setFillColor(sf::Color::Red);
		point.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

		ShapeSelector::shapes.polygons.back().points.push_back(point);
	}
}

void DrawManager::handleSavePosition(sf::RenderWindow& window, sf::Event& event)
{
	if (event.key.code == sf::Keyboard::Enter)
	{
		ShapeSelector::movingShape = ShapeType::Nothing;
		ShapeSelector::selectedShape = ShapeType::Nothing;
	}
}

void DrawManager::handleSizeIncrease(sf::RenderWindow& window, sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
		switch (ShapeSelector::movingShape)
		{
			case ShapeType::Rectangle: {
				auto& rectangle = ShapeSelector::shapes.rectangles.back();
				rectangle.setSize(sf::Vector2f(rectangle.getSize().x + rectangle.getSize().x * 0.1, rectangle.getSize().y + rectangle.getSize().y * 0.1));
				clampShapeSize(rectangle);
				rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
				break;
			}
			case ShapeType::Circle: {
				auto& circle = ShapeSelector::shapes.circles.back();
				circle.setRadius(circle.getRadius() + circle.getRadius() * 0.1);
				clampShapeSize(circle);
				circle.setOrigin(circle.getRadius(), circle.getRadius());
				break;
			}
			case ShapeType::Triangle: {
				auto& triangle = ShapeSelector::shapes.triangles.back();
				triangle.setRadius(triangle.getRadius() + triangle.getRadius() * 0.1);
				clampShapeSize(triangle);
				triangle.setOrigin(triangle.getRadius(), triangle.getRadius());
				break;
			}
			case ShapeType::Nothing:
				break;
			default:
				break;
		}
}

void DrawManager::handleSizeDecrease(sf::RenderWindow& window, sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
		switch (ShapeSelector::movingShape)
		{
			case ShapeType::Rectangle: {
				auto& rectangle = ShapeSelector::shapes.rectangles.back();
				rectangle.setSize(sf::Vector2f(rectangle.getSize().x - rectangle.getSize().x * 0.1, rectangle.getSize().y - rectangle.getSize().y * 0.1));
				clampShapeSize(rectangle);
				rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
				break;
			}
			case ShapeType::Circle: {
				auto& circle = ShapeSelector::shapes.circles.back();
				circle.setRadius(circle.getRadius() - circle.getRadius() * 0.1);
				clampShapeSize(circle);
				circle.setOrigin(circle.getRadius(), circle.getRadius());
				break;
			}
			case ShapeType::Triangle: {
				auto& triangle = ShapeSelector::shapes.triangles.back();
				triangle.setRadius(triangle.getRadius() - triangle.getRadius() * 0.1);
				clampShapeSize(triangle);
				triangle.setOrigin(triangle.getRadius(), triangle.getRadius());
				break;
			}
			case ShapeType::Nothing:
				break;
			default:
				break;
		}
}

void DrawManager::clampShapeSize(sf::RectangleShape& shape)
{
	float x = shape.getSize().x, y = shape.getSize().y;

	clamp(300, 50, x);
	clamp(300, 50, y);

	shape.setSize(sf::Vector2f(x, y));
}

void DrawManager::clampShapeSize(sf::CircleShape& shape)
{
	float radius = shape.getRadius();

	clamp(300, 50, radius);

	shape.setRadius(radius);
}

void DrawManager::drawLinesBetweenPolygonPoints(sf::RenderWindow& window)
{
	if (ShapeSelector::shapes.polygons.size() > 0)
	{
		for (auto& polygon : ShapeSelector::shapes.polygons)
		{
			auto& points = ShapeSelector::shapes.polygons.back().points;

			for (int i = 0; i < points.size() - 1; i++)
			{
				sf::Vertex line[] = {
					sf::Vertex(points[i].getPosition()),
					sf::Vertex(points[i + 1].getPosition())
				};

				window.draw(line, 5, sf::Lines);
				window.display();
			}
		}
	}
}
}