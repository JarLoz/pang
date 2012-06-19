#pragma once
#include "VisibleGameObject.h"


class GameObjectManager
{
public:	
	GameObjectManager();
	~GameObjectManager();

	void Add(std::string name, VisibleGameObject* gameObject);
	void AddTile(std::string name, VisibleGameObject* tile);

	void Remove(std::string name);
	void RemoveTile(std::string name);

	int GetObjectCount() const;

	VisibleGameObject* Get(std::string name) const;
	std::map<std::string, VisibleGameObject*> GetGameTiles() const;

	void DrawAll(sf::RenderWindow& renderWindow);
	void UpdateAll();

private:
	std::map<std::string, VisibleGameObject*> _gameObjects;
	std::map<std::string, VisibleGameObject*> _gameTiles;

	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string,VisibleGameObject*> & p) const
		{
			delete p.second;
		}
	};
};
