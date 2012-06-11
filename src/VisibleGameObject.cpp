#include "stdafx.h"
#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject()
{
	_isLoaded = false;
}

VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::Load(std::string filename)
{
	if(_image.LoadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;
		_sprite.SetImage(_image);
		_isLoaded = true;
	}
}

void VisibleGameObject::Draw(sf::RenderWindow & renderWindow)
{
	if(_isLoaded)
	{
		renderWindow.Draw(_sprite);
	}
}

void VisibleGameObject::SetPosition(float x, float y)
{
	if (_isLoaded)
	{
		_sprite.SetPosition(x,y);
	}
}
