#include "stdafx.h"
#include "GameTile.h"

GameTile::GameTile()
{
	Load("images/Tile.png");
	assert(IsLoaded());

	GetSprite().SetCenter(GetSprite().GetSize().x /2, GetSprite().GetSize().y / 2);

}

GameTile::~GameTile()
{
}
