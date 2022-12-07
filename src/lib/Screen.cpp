#include "Screen.hpp"
#include "FirstImage.hpp"
#include "StartMenu.hpp"

namespace my
{
ScreenType Screen::currentScreen = ScreenType::StartMenu;

void Screen::nextScreen()
{
	if (currentScreen < ScreenType::EndMenu)
		currentScreen = static_cast<ScreenType>(static_cast<int>(currentScreen) + 1);
}

void Screen::previousScreen()
{
	if (currentScreen > ScreenType::StartMenu)
		currentScreen = static_cast<ScreenType>(static_cast<int>(currentScreen) - 1);
}

void Screen::goToScreen(ScreenType screen)
{
	if (screen >= ScreenType::StartMenu && screen <= ScreenType::EndMenu)
		currentScreen = screen;
}

void Screen::screenHandler(sf::RenderWindow& window, sf::Event& event)
{
	switch (currentScreen)
	{
		case ScreenType::StartMenu:
			StartMenu::initialize();
			StartMenu::display(window);
			StartMenu::handleKeyPress(event, window);
			break;
		case ScreenType::FirstImage:
			FirstImage::display(window);
			FirstImage::handleEvents(window, event);
			break;
		case ScreenType::SecondImage:
			break;
		case ScreenType::Morphing:
			break;
		case ScreenType::EndMenu:
			break;
		default:
			break;
	}
}

}