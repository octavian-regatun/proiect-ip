#include "MyScreen.hpp"

MyScreenEnum MyScreen::currentScreen = MyScreenEnum::Start;

void MyScreen::nextScreen()
{
	if (currentScreen < MyScreenEnum::End)
		currentScreen = (MyScreenEnum)(currentScreen + 1);
}

void MyScreen::previousScreen()
{
	if (currentScreen > MyScreenEnum::Start)
		currentScreen = (MyScreenEnum)(currentScreen - 1);
}

void MyScreen::goToScreen(MyScreenEnum screen)
{
	if (screen >= MyScreenEnum::Start && screen <= MyScreenEnum::End)
		currentScreen = screen;
}