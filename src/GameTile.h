#pragma once
#include "VisibleGameObject.h"

class GameTile :
	public VisibleGameObject
{
	public:
		GameTile();
		~GameTile();

		void Draw(sf::RenderWindow& rw);

		void SetDestroyed(bool state);

	private:
		bool isDestroyed;
};
