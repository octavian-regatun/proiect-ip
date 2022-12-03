#include "Screen.hpp"

namespace my
{
ScreenType Screen::currentScreen = ScreenType::Start;

void Screen::nextScreen()
{
	if (currentScreen < ScreenType::End)
		currentScreen = (ScreenType)(currentScreen + 1);
}

void Screen::previousScreen()
{
	if (currentScreen > ScreenType::Start)
		currentScreen = (ScreenType)(currentScreen - 1);
}

void Screen::goToScreen(ScreenType screen)
{
	if (screen >= ScreenType::Start && screen <= ScreenType::End)
		currentScreen = screen;
}
}