#include "Sound.hpp"
#include "Button.hpp"
#include "ColorSelector.hpp"
#include "Font.hpp"

namespace my
{
sf::SoundBuffer Sound::buffer = sf::SoundBuffer();
sf::Sound Sound::sound = sf::Sound();
bool Sound::isPlaying = false;

void Sound::playSound()
{
	buffer.loadFromFile("sound.ogg");
	sound.setBuffer(buffer);
	sound.play();
}

void Sound::stopSound()
{
	sound.stop();
}

void Sound::toggleSound()
{
	if (isPlaying)
	{
		stopSound();
		isPlaying = false;
	}
	else
	{
		playSound();
		isPlaying = true;
	}
}

void Sound::displayButton(sf::RenderWindow& window)
{
	Button soundButton(window, ColorSelector::buttonColor, 200, 50, window.getSize().x / 2, window.getSize().y / 2 + 70);
	soundButton.setText(window, ColorSelector::textColor, "SOUND   ", Font::font, 24);

	// on button click toggle sound without using setOnClick

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (soundButton.button.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			toggleSound();
		}
	}
}
}