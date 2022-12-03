#include "AllButtons.hpp"
#include "MyButton.hpp"

namespace my
{
std::vector<MyButton> AllButtons::buttons = std::vector<MyButton>();

void AllButtons::handleEvents(sf::RenderWindow& window, sf::Event& ev)
{
	for (auto& myButton : buttons)
		if (myButton.button.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			if (ev.type == sf::Event::MouseButtonPressed)
				if (ev.mouseButton.button == sf::Mouse::Left)
				{
					auto func = myButton.getOnClick();
					func();
				}
}
}