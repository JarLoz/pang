#include "stdafx.h"
#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow & renderWindow)
{
	sf::Image image;
	if(image.LoadFromFile("images/Splashscreen.png") != true)
	{
		return;
	}

	sf::Sprite sprite(image);

	renderWindow.Draw(sprite);
	renderWindow.Display();

	sf::Event event;

	while(true)
	{
		while(renderWindow.GetEvent(event))
		{
			if(event.Type == sf::Event::EventType::KeyPressed
					|| event.Type == sf::Event::EventType::MouseButtonPressed
					|| event.Type == sf::Event::EventType::Closed )
			{
				return;
			}
		}
	}
}
