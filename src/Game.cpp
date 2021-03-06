#include "stdafx.h"
#include "Game.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "SFMLSoundProvider.h"
#include "ServiceLocator.h"

void Game::Start(void)
{
	if(_gameState != Uninitialized)
		return;

	_mainWindow.Create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGTH,32),"Pang!");


	SFMLSoundProvider *soundProvider = new SFMLSoundProvider();

	ServiceLocator::RegisterServiceLocator(soundProvider);

	ServiceLocator::GetAudio()->PlaySong("audio/Soundtrack.ogg",true);

	//_mainWindow.SetFramerateLimit(60);

	PlayerPaddle *player1 = new PlayerPaddle();
	player1->SetPosition((SCREEN_WIDTH/2),700);

	GameBall *ball = new GameBall();
	ball->SetPosition((SCREEN_WIDTH/2),(SCREEN_HEIGTH/2)-15);

	GameTile *tile = new GameTile();
	tile->SetPosition((SCREEN_WIDTH/2),(SCREEN_HEIGTH/2)-50);

	GameTile *tile2 = new GameTile();
	tile2->SetPosition(tile->GetPosition().x + tile->GetWidth(),(SCREEN_HEIGTH/2)-50);

	_gameObjectManager.Add("Paddle1",player1);
	_gameObjectManager.Add("Ball",ball);
	_gameObjectManager.AddTile("tile1",tile);
	_gameObjectManager.AddTile("tile2",tile2);

	_gameState = Game::ShowingSplash;

	while(!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.Close();
}

bool Game::IsExiting(){
	if(_gameState == Game::Exiting)
		return true;
	else
		return false;
}

sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

const sf::Input& Game::GetInput()
{
	return _mainWindow.GetInput();
}

GameObjectManager& Game::GetGameObjectManager()
{
	return _gameObjectManager;
}

void Game::GameLoop(){
	sf::Event currentEvent;
	_mainWindow.GetEvent(currentEvent);

	switch(_gameState)
	{
		case Game::ShowingMenu:
			{
				ShowMenu();
				break;
			}
		case Game::ShowingSplash:
			{
				ShowSplashScreen();
				break;
			}
		case Game::Playing:
			{

				_mainWindow.Clear(sf::Color(sf::Color(0,0,0)));
				_gameObjectManager.UpdateAll();
				_gameObjectManager.DrawAll(_mainWindow);

				_mainWindow.Display();


				if(currentEvent.Type == sf::Event::Closed)
					_gameState = Game::Exiting;

				if(currentEvent.Type == sf::Event::KeyPressed)
				{
					if(currentEvent.Key.Code == sf::Key::Escape) ShowMenu();
				}

				break;
			}
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch(result)
	{
		case MainMenu::Exit:
			_gameState = Game::Exiting;
			break;
		case MainMenu::Play:
			_gameState = Game::Playing;
			break;
	}
}
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
