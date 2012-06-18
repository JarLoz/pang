#include "stdafx.h"
#include "GameTile.h"

GameTile::GameTile():
	isDestroyed(false)
{
	Load("images/Tile.png");
	assert(IsLoaded());

	GetSprite().SetCenter(GetSprite().GetSize().x /2, GetSprite().GetSize().y / 2);

}

GameTile::~GameTile()
{
}

void GameTile::Draw(sf::RenderWindow & window)
{
	if(!isDestroyed)
		VisibleGameObject::Draw(window);
}

void GameTile::SetDestroyed(bool state)
{
	isDestroyed = state;
}
