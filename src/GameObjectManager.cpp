#include "stdafx.h"
#include "GameObjectManager.h"
#include "Game.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	std::for_each(_gameObjects.begin(),_gameObjects.end(),GameObjectDeallocator());
	std::for_each(_gameTiles.begin(),_gameTiles.end(),GameObjectDeallocator());
}

void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject)
{
	_gameObjects.insert(std::pair<std::string,VisibleGameObject*>(name,gameObject));
}

void GameObjectManager::AddTile(std::string name, VisibleGameObject* tile)
{
	_gameTiles.insert(std::pair<std::string,VisibleGameObject*>(name,tile));
}

void GameObjectManager::Remove(std::string name) 
{
	std::map<std::string, VisibleGameObject*>::iterator results = _gameObjects.find(name);
	if (results != _gameObjects.end() )
	{
		delete results->second;
		_gameObjects.erase(results);
	}
}

void GameObjectManager::RemoveTile(std::string name) 
{
	std::map<std::string, VisibleGameObject*>::iterator results = _gameTiles.find(name);
	if (results != _gameTiles.end() )
	{
		delete results->second;
		_gameObjects.erase(results);
	}
}

VisibleGameObject* GameObjectManager::Get(std::string name) const
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
	if(results == _gameObjects.end())
		return NULL;
	return results->second;
}

std::map<std::string, VisibleGameObject*> GameObjectManager::GetGameTiles() const{
	return _gameTiles;
}

int GameObjectManager::GetObjectCount() const
{
	return _gameObjects.size() + _gameTiles.size();
}

void GameObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();

	while(itr != _gameObjects.end())
	{
		itr->second->Draw(renderWindow);
		itr++;
	}

	itr = _gameTiles.begin();
	while(itr != _gameTiles.end())
	{
		itr->second->Draw(renderWindow);
		itr++;
	}
}

void GameObjectManager::UpdateAll()
{
	std::map<std::string,VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	float timeDelta = Game::GetWindow().GetFrameTime();

	while (itr != _gameObjects.end())
	{
		itr->second->Update(timeDelta);
		itr++;
	}

	itr = _gameTiles.begin();

	while (itr != _gameTiles.end())
	{
		itr->second->Update(timeDelta);
		itr++;
	}
}
