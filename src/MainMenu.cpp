#include "stdafx.h"
#include "MainMenu.h"
#include "ServiceLocator.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
	//Loading menu image
	sf::Image image;
	image.LoadFromFile("images/Mainmenu.png");
	sf::Sprite sprite(image);

	//Clickable regions
	
	//Play menu item
	
	MenuItem playButton;
	playButton.rect.Top= 145;
	playButton.rect.Bottom= 380;
	playButton.rect.Left= 0;
	playButton.rect.Right= 1023;
	playButton.action = Play;

	MenuItem exitButton;
	exitButton.rect.Top = 383;
	exitButton.rect.Bottom = 560;
	exitButton.rect.Left = 0;
	exitButton.rect.Right = 1023;
	exitButton.action = Exit;

	menuItems.push_back(playButton);
	menuItems.push_back(exitButton);

	window.Draw(sprite);
	window.Display();

	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;
	for (it = menuItems.begin(); it != menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if( menuItemRect.Bottom > y
				&& menuItemRect.Top < y
				&& menuItemRect.Left < x
				&& menuItemRect.Right > x )
		{
			return (*it).action;
		}

	}

	return Nothing;
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while(true)
	{
		while(window.GetEvent(menuEvent))
		{
			if(menuEvent.Type == sf::Event::MouseButtonPressed)
			{
				if(ServiceLocator::GetAudio()->IsSongPlaying())
					//ServiceLocator::GetAudio()->StopAllSounds();
				return HandleClick(menuEvent.MouseButton.X, menuEvent.MouseButton.Y);
			}
			if(menuEvent.Type == sf::Event::Closed)
			{
				return Exit;
			}
		}
	}
}
