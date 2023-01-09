#include "StartMenu.hpp"
#include "AllButtons.hpp"
#include "Button.hpp"
#include "ColorSelector.hpp"
#include "Font.hpp"
#include "Screen.hpp"
#include "ShapeSelector.hpp"
#include "Sound.hpp"
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
	window.clear(ColorSelector::backgroundColor);
	displayTitle(window);
	displayButtons(window);
	Sound::displayButton(window);
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
	title.setFillColor(my::ColorSelector::textColor);
	window.draw(title);
}

void StartMenu::displayButtons(sf::RenderWindow& window)
{
	int x = window.getSize().x / 2.f;
	int y = window.getSize().y / 2.f;

	//button for create feature
	int length = 200;
	int height = 50;

	Button createButton(window, ColorSelector::buttonColor, length, height, x, y);
	//ca textul sa se incadreze in centrul butonului ar trebui sa schimbi valorile length,height sau chSize(24)
	createButton.setText(window, ColorSelector::textColor, "CREATE IMAGE", Font::font, 24);
	createButton.setOnClick([]() { AllButtons::buttons.clear(); Screen::goToScreen(ScreenType::FirstImage); });

	Button colorPallete(window, ColorSelector::buttonColor, length, height, x, y + 100);
	//ca textul sa se incadreze in centrul butonului ar trebui sa schimbi valorile length,height sau chSize(24)
	colorPallete.setText(window, ColorSelector::textColor, "CHANGE COLOR", Font::font, 24);
	colorPallete.setOnClick([]() {	AllButtons::buttons.clear(); Screen::goToScreen(ScreenType::ColorPalette); });
}

void StartMenu::handleKeyPress(sf::Event& event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape)
			window.close();
}
}
