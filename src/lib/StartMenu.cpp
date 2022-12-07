#include "StartMenu.hpp"
#include "Button.hpp"
#include "Color.hpp"
#include "Font.hpp"
#include "Screen.hpp"
#include "ShapeSelector.hpp"
#include <SFML/Graphics.hpp>

namespace my
{
void StartMenu::initialize()
{
	// reinitializam shapeCounterurile cand ajungem iarasi in Menu
	ShapeSelector::refreshShapesCount();
}

void StartMenu::display(sf::RenderWindow& window)
{
	window.clear(Color::backgroundColor);
	displayTitle(window);
	displayButtons(window);
	window.display();
}

void StartMenu::displayTitle(sf::RenderWindow& window)
{
	int x = window.getSize().x / 2.f;

	sf::Text title;

	title.setString("MENU");
	title.setFont(my::Font::fontBold);
	title.setCharacterSize(70);
	title.setPosition(x - 100, 100);
	title.setFillColor(my::Color::textColor);
	window.draw(title);
}

void StartMenu::displayButtons(sf::RenderWindow& window)
{
	int x = window.getSize().x / 2.f;
	int y = window.getSize().y / 2.f;

	//button for create feature
	int length = 200;
	int height = 50;

	Button createButton(window, Color::buttonColor, length, height, x, y);
	//ca textul sa se incadreze in centrul butonului ar trebui sa schimbi valorile length,height sau chSize(24)
	createButton.setText(window, Color::textColor, "CREATE IMAGE", Font::font, 24);
	createButton.setOnClick([]() { Screen::goToScreen(ScreenType::FirstImage); });
}

void StartMenu::handleKeyPress(sf::Event& event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape)
			window.close();
}
}
