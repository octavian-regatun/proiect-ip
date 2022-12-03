#include "MyButton.hpp"
#include <SFML/Graphics.hpp>

namespace my
{
class AllButtons
{
public:
	static std::vector<MyButton> buttons;
	static void handleEvents(sf::RenderWindow& window, sf::Event& ev);
};
}