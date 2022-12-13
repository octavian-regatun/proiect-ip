#include "MenuSelector.hpp"
#include "AllButtons.hpp"
#include "Button.hpp"
#include "ColorSelector.hpp"
#include "Font.hpp"
#include "ShapeSelector.hpp"

namespace my
{
MenuSelectorType MenuSelector::activeMenuSelector = MenuSelectorType::ShapeSelector;

void MenuSelector::toggleMenuSelector()
{
	switch (activeMenuSelector)
	{
		case MenuSelectorType::ShapeSelector:
			activeMenuSelector = MenuSelectorType::ColorSelector;
			break;
		case MenuSelectorType::ColorSelector:
			activeMenuSelector = MenuSelectorType::ShapeSelector;
			break;

		default:
			break;
	}
}

void MenuSelector::drawButtons(sf::RenderWindow& window)
{
	unsigned int length = 75, height = 50, fontSize = 18;
	Button previousButton(window, ColorSelector::buttonColor, length, height, 50, window.getSize().y - 100);
	previousButton.setText(window, ColorSelector::textColor, "Previous", Font::font, fontSize);
	previousButton.setOnClick([]() { toggleMenuSelector(); });

	Button nextButton(window, ColorSelector::buttonColor, length, height, window.getSize().y - 50, window.getSize().y - 100);
	nextButton.setText(window, ColorSelector::textColor, "Next", Font::font, fontSize);
	nextButton.setOnClick([]() { toggleMenuSelector(); });
}

void MenuSelector::disableShapeButtons()
{
	for (Button& button : AllButtons::buttons)
		if (button.text.getString() == "RECTANGLE" || button.text.getString() == "CIRCLE  " || button.text.getString() == "TRIANGLE" || button.text.getString() == "POLYGON")
			button.isActive = false;
}

void MenuSelector::disableColorButtons()
{
	for (Button& button : ColorSelector::colorButtons)
		if (button.text.getString() == "COLOR")
			button.isActive = false;
}

void MenuSelector::enableShapeButtons()
{
	for (Button& button : AllButtons::buttons)
		if (button.text.getString() == "RECTANGLE" || button.text.getString() == "CIRCLE  " || button.text.getString() == "TRIANGLE" || button.text.getString() == "POLYGON")
			button.isActive = true;
}

void MenuSelector::enableColorButtons()
{
	for (Button& button : ColorSelector::colorButtons)
		if (button.text.getString() == "COLOR")
			button.isActive = true;
}

void MenuSelector::displayMenu(sf::RenderWindow& window)
{
	switch (activeMenuSelector)
	{
		case MenuSelectorType::ShapeSelector:
			ShapeSelector::displayMenu(window);
			disableColorButtons();
			enableShapeButtons();
			break;
		case MenuSelectorType::ColorSelector:
			ColorSelector::displayMenu(window);
			disableShapeButtons();
			enableColorButtons();
			break;

		default:
			break;
	}
}
}