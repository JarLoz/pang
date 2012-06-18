#pragma once
#include "PlayerPaddle.h"
#include "VisibleGameObject.h"

class GameBall :
	public VisibleGameObject
{
	public:
		GameBall();
		virtual ~GameBall();
		void Update(float);
		
	private:
		float _velocity;
		float _angle;
		float _elapsedTimeSinceStart;

		enum Direction {UP, DOWN, LEFT, RIGHT};

		float LinearVelocityX(float angle);
		float LinearVelocityY(float angle);

		void ResolveSideCollision(float& moveByX);
		void ResolveTopCollision(float& moveByY);
		void ResolveBottomCollision(float moveByY);

		void ResolvePlayerPaddleCollision(PlayerPaddle* player1, float& moveByY, float& moveByX);
		void ResolveGameTileCollision(float& moveByY, float& moveByX);

		Direction GetCollisionDirection(sf::Rect<float>, sf::Rect<float>, float, float);


};
