#include "stdafx.h"
#include "PlayerPaddle.h"
#include "Game.h"

PlayerPaddle::PlayerPaddle():
	_velocity(0),
	_maxVelocity(600.0f),
	_acceleration(800.0f)
{
	Load("images/paddle.png");
	assert(IsLoaded());

	GetSprite().SetCenter(GetSprite().GetSize().x /2, GetSprite().GetSize().y / 2);
}

PlayerPaddle::~PlayerPaddle()
{
}

void PlayerPaddle::Draw(sf::RenderWindow & window)
{
	VisibleGameObject::Draw(window);
}

float PlayerPaddle::GetVelocity() const
{
	return _velocity;
}

void PlayerPaddle::Update(float elapsedTime)
{
	if(Game::GetInput().IsKeyDown(sf::Key::Left))
	{
		_velocity -= _acceleration * elapsedTime;
	}
	else if(Game::GetInput().IsKeyDown(sf::Key::Right))
	{
		_velocity += _acceleration * elapsedTime;
	}
	else if(Game::GetInput().IsKeyDown(sf::Key::Down))
	{
		_velocity = 0.0f;
	}
	else
	{
		reduceSpeed(elapsedTime);
	}
	if(_velocity > _maxVelocity)
		_velocity = _maxVelocity;
	if(_velocity < -_maxVelocity)
		_velocity = -_maxVelocity;

	sf::Vector2f pos = this->GetPosition();

	if(pos.x < GetSprite().GetSize().x/2)
	{
		_velocity = -_velocity;
		SetPosition(GetWidth()/2, GetPosition().y);
	}
	if(pos.x > (Game::SCREEN_WIDTH - GetSprite().GetSize().x/2))
	{
		_velocity = -_velocity;
		SetPosition(Game::SCREEN_WIDTH - GetWidth()/2, GetPosition().y);
	}

	GetSprite().Move(_velocity * elapsedTime, 0);
}

void PlayerPaddle::reduceSpeed(float elapsedTime)
{
	if(_velocity > 0)
	{
		if(_velocity < _acceleration * elapsedTime)
			_velocity = 0.0f;
		else
			_velocity -= _acceleration * elapsedTime;
	}
	else if (_velocity < 0)
	{
		if(_velocity > -_acceleration * elapsedTime)
			_velocity = 0.0f;
		else
			_velocity += _acceleration * elapsedTime;
	}
}
