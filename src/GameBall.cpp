#include "stdafx.h"
#include "GameBall.h"
#include "Game.h"


GameBall::GameBall() :
	_velocity(230.0f),
	_elapsedTimeSinceStart(0.0f)
{
	Load("images/ball.png");
	assert(IsLoaded());


	GetSprite().SetCenter(15,15);

	sf::Randomizer::SetSeed(std::clock());
	_angle = (float)sf::Randomizer::Random(0,360);
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
	
	moveByX = ResolveSideCollision(moveByX);

	//Collision with player paddle

	moveByY = ResolvePlayerPaddleCollision(player1, moveByY);

	//Collision with top and bottom

	moveByY = ResolveTopCollision(moveByY);

	ResolveBottomCollision(moveByY);

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

float GameBall::ResolveSideCollision(float moveByX)
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

	return moveByX;
}

float GameBall::ResolveTopCollision(float moveByY)
{
	if(GetPosition().y - GetHeight()/2 + moveByY <= 0)
	{
		_angle = 180.0f - _angle;
		moveByY = -moveByY;
	}

	return moveByY;
}

void GameBall::ResolveBottomCollision(float moveByY)
{
	if(GetPosition().y + GetHeight()/2 + moveByY >= Game::SCREEN_HEIGTH)
	{
		GetSprite().SetPosition(Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGTH/2);
		_angle = (float)sf::Randomizer::Random(0,360);
		_velocity = 220.0f;
		_elapsedTimeSinceStart = 0.0f;
	}
}

float GameBall::ResolvePlayerPaddleCollision(PlayerPaddle* player1, float moveByY)
{
	sf::Rect<float> p1BB = player1->GetBoundingRect();

	if(p1BB.Intersects(GetBoundingRect()))
	{
		_angle = 360.0f - (_angle - 180.0f);
		if(_angle > 360.0f) _angle -= 360.0f;

		moveByY = -moveByY;

		//Making sure ball ain't in paddle, son
		
		if(GetBoundingRect().Bottom > player1->GetBoundingRect().Top)
		{
			SetPosition(GetPosition().x,player1->GetBoundingRect().Top - GetHeight()/2 -1);
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
	}

	return moveByY;
}
