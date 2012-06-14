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

		float LinearVelocityX(float angle);
		float LinearVelocityY(float angle);

		float ResolveSideCollision(float moveByX);
		float ResolveTopCollision(float moveByY);
		void ResolveBottomCollision(float moveByY);

		float ResolvePlayerPaddleCollision(PlayerPaddle* player1, float moveByY);
};
