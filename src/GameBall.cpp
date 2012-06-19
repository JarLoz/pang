#include "stdafx.h"
#include "GameBall.h"
#include "GameTile.h"
#include "Game.h"
#include "ServiceLocator.h"


GameBall::GameBall() :
	_velocity(230.0f),
	_elapsedTimeSinceStart(0.0f)
{
	Load("images/ball.png");
	assert(IsLoaded());


	GetSprite().SetCenter(15,15);

	sf::Randomizer::SetSeed(std::clock());
	_angle = (float)sf::Randomizer::Random(90,270);
}

GameBall::~GameBall()
{
}

void GameBall::Update(float elapsedTime)
{
	PlayerPaddle* player1 = dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle1"));
	if(player1 == NULL)
		return;

	_elapsedTimeSinceStart += elapsedTime;

	if(_elapsedTimeSinceStart < 3.0f)
	{
		return;
	}

	float moveAmount = _velocity * elapsedTime;

	float moveByX = LinearVelocityX(_angle) * moveAmount;
	float moveByY = LinearVelocityY(_angle) * moveAmount;

	//Collision with sides of the screen
	
	ResolveSideCollision(moveByX);

	//Collision with top and bottom
	
	ResolveTopCollision(moveByY);
	ResolveBottomCollision(moveByY);

	//Collision with player paddle

	ResolvePlayerPaddleCollision(player1, moveByY, moveByX);

	//Collision with game tile
	
	//ResolveGameTileCollision(moveByY, moveByX);



	GetSprite().Move(moveByX,moveByY);



}

// WARNING: DANGEROUS MATH MAGIC STARTS

float GameBall::LinearVelocityX(float angle)
{
	angle -= 90;
	if (angle < 0) angle = 360 + angle;
	return (float)std::cos( angle * (3.1415926 / 180.0f));
}


float GameBall::LinearVelocityY(float angle)
{
	angle -= 90;
	if (angle < 0) angle = 360 + angle;
	return (float)std::sin( angle * (3.1415926 / 180.0f));
}


// DANGEROUS MATH MAGIC ENDS

void GameBall::ResolveSideCollision(float& moveByX)
{
	if(GetPosition().x + moveByX <= 0 + GetWidth()/2
			|| GetPosition().x + GetWidth()/2 + moveByX >= Game::SCREEN_WIDTH)
	{
		//RICOCHET!
		_angle = 360.0f - _angle;
		if(_angle > 260.0f && _angle < 280.0f) _angle += 20.0f;
		if(_angle > 80.0f && _angle < 100.0f) _angle += 20.0f;
		moveByX = -moveByX;
	}
}

void GameBall::ResolveTopCollision(float& moveByY)
{
	if(GetPosition().y - GetHeight()/2 + moveByY <= 0)
	{
		_angle = 180.0f - _angle;
		moveByY = -moveByY;
	}
}

void GameBall::ResolveBottomCollision(float moveByY)
{
	if(GetPosition().y + GetHeight()/2 + moveByY >= Game::SCREEN_HEIGTH)
	{
		GetSprite().SetPosition(Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGTH/2);
		_angle = (float)sf::Randomizer::Random(90,270);
		_velocity = 220.0f;
		_elapsedTimeSinceStart = 0.0f;
	}
}


void GameBall::ResolveGameTileCollision(float& moveByY, float& moveByX)
{
	GameTile* tile = dynamic_cast<GameTile*>(Game::GetGameObjectManager().Get("Tile"));
	if(tile == NULL)
		return;


	sf::Rect<float> tileBB = tile->GetBoundingRect();
	sf::Rect<float> ballBB = GetBoundingRect();

	if(tileBB.Intersects(ballBB))
	{
		Direction dir = GetCollisionDirection(ballBB, tileBB, moveByY, moveByX);
		switch(dir)
		{
			case UP:
				{
					_angle = 360.0f - (_angle - 180.0f);
					if(_angle > 360.0f) _angle -= 360.0f;
					moveByY = -moveByY;

					if(ballBB.Bottom > tileBB.Top)
					{
						SetPosition(GetPosition().x,tileBB.Top - GetHeight()/2 - 1);
					}
					break;
				}
			case DOWN:
				{
					_angle = 180.0f - _angle;
					moveByY = -moveByY;

					if(ballBB.Top < tileBB.Bottom)
					{
						SetPosition(GetPosition().x,tileBB.Bottom + GetHeight()/2 + 1);
					}
					break;
				}
			case LEFT:
				{
					_angle = 360.0f - _angle;
					moveByX = -moveByX;

					if(ballBB.Right > tileBB.Left)
					{
						SetPosition(tileBB.Left - GetWidth()/2 -1,GetPosition().y);
					}
					break;
				}
			case RIGHT:
				{
					_angle = 360.0f - _angle;
					moveByX = -moveByX;

					if(ballBB.Left < tileBB.Right)
					{
						SetPosition(tileBB.Right + GetWidth()/2 +1,GetPosition().y);
					}
					break;
				}
			default:
				{
					break;
				}
		}

		
		tile->SetDestroyed(true);
		Game::GetGameObjectManager().Remove("Tile");

		_velocity += 5.0f;

		ServiceLocator::GetAudio()->PlaySound("audio/kaboom.wav");
	}
}
void GameBall::ResolvePlayerPaddleCollision(PlayerPaddle* player1, float& moveByY, float& moveByX)
{
	sf::Rect<float> p1BB = player1->GetBoundingRect();
	sf::Rect<float> ballBB = GetBoundingRect();

	if(p1BB.Intersects(ballBB))
	{

		Direction dir = GetCollisionDirection(ballBB, p1BB, moveByY, moveByX);
		switch(dir)
		{
			case UP:
				{
					_angle = 360.0f - (_angle - 180.0f);
					if(_angle > 360.0f) _angle -= 360.0f;
					moveByY = -moveByY;

					if(ballBB.Bottom > p1BB.Top)
					{
						SetPosition(GetPosition().x,p1BB.Top - GetHeight()/2 - 1);
					}
					break;
				}
			case DOWN:
				{
					_angle = 180.0f - _angle;
					moveByY = -moveByY;

					if(ballBB.Top < p1BB.Bottom)
					{
						SetPosition(GetPosition().x,p1BB.Bottom + GetHeight()/2 + 1);
					}
					break;
				}
			case LEFT:
				{
					_angle = 360.0f - _angle;
					moveByX = -moveByX;

					if(ballBB.Right > p1BB.Left)
					{
						SetPosition(p1BB.Left - GetWidth()/2 -1,GetPosition().y);
					}
					break;
				}
			case RIGHT:
				{
					_angle = 360.0f - _angle;
					moveByX = -moveByX;

					if(ballBB.Left < p1BB.Right)
					{
						SetPosition(p1BB.Right + GetWidth()/2 +1,GetPosition().y);
					}
					break;
				}
			default:
				{
					break;
				}
		}



		// Adding ENGLISH
		// wtf is ENGLISH anyway
		// GAMEPLAY FEATURE LAWL

		float playerVelocity = player1->GetVelocity();

		if(playerVelocity < 0)
		{
			//moving left
			_angle -= 20.0f;
			if(_angle < 0) _angle = 360.0f - _angle;
		}
		else if (playerVelocity > 0)
		{
			//moving right

			_angle += 20.0f;
			if(_angle > 360.0f) _angle = _angle - 360.0f;
		}

		_velocity += 5.0f;

		ServiceLocator::GetAudio()->PlaySound("audio/kaboom.wav");
	}

}

GameBall::Direction GameBall::GetCollisionDirection(sf::Rect<float> ballRect, sf::Rect<float> objectRect, float bMoveByX, float bMoveByY)
{
	Direction dir;
	if (ballRect.Left >= objectRect.Left && ballRect.Right <= objectRect.Right)
	{
		//Straight X-axis collision (no side clipping)
		if (ballRect.Bottom >= objectRect.Top && ballRect.Top <= objectRect.Top)
			dir = UP;
		else
			dir = DOWN;
	} else if (ballRect.Top >= objectRect.Top && ballRect.Bottom <= objectRect.Bottom)
	{
		//Straight Y-axis collision (no side clipping)
		
		if (ballRect.Right >= objectRect.Left && ballRect.Left <= objectRect.Left)
			dir = LEFT;
		else
			dir = RIGHT;
	} else
	{
		//Side clipping! This is where the fun stuff is.
		
		float distX = std::min(std::abs(ballRect.Left-objectRect.Right),std::abs(ballRect.Right-objectRect.Left));
		float distY = std::min(std::abs(ballRect.Top-objectRect.Bottom),std::abs(ballRect.Bottom-objectRect.Top));


		float timeX = distX/bMoveByX;
		float timeY = distY/bMoveByY;

		if(timeX > timeY)
		{
			// X-axis collision!
			if (ballRect.Bottom >= objectRect.Top && ballRect.Top <= objectRect.Top)
				dir = UP;
			else
				dir = DOWN;
		}else
		{
			// Y-axis collision
			if (ballRect.Right >= objectRect.Left && ballRect.Left <= objectRect.Left)
				dir = LEFT;
			else
				dir = RIGHT;
		}

	}

	return dir;
}
