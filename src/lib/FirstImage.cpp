#include "FirstImage.hpp"
#include "Button.hpp"
#include "Color.hpp"
#include "DrawManager.hpp"
#include "Font.hpp"
#include "Screen.hpp"
#include "ShapeSelector.hpp"

namespace my
{
void FirstImage::display(sf::RenderWindow& window)
{
	window.clear(Color::backgroundColor);
	ShapeSelector::displayMenu(window);
	DrawManager::drawShapes(window);
	window.display();
}

void FirstImage::handleEvents(sf::RenderWindow& window, sf::Event& event)
{
	ShapeSelector::handleShapeSelection(window, event);
	ShapeSelector::handlePolygonFinish(window, event);
	DrawManager::handleEvents(window, event);
}
}