#include "stdafx.h"
#include "GameBall.h"


GameBall::GameBall()
{
	Load("images/ball.png");
	assert(IsLoaded());

	GetSprite().SetCenter(15,15);
}

GameBall::~GameBall()
{
}


