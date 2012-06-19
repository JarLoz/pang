#include "stdafx.h"
#include "VisibleGameObject.h"
#include "ImageFileCache.h"

VisibleGameObject::VisibleGameObject() :
	_isLoaded(false)
{
}

VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::Load(std::string filename)
{
/*	if(_image.LoadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;
		_sprite.SetImage(_image);
		_isLoaded = true;
	}*/

	_filename = filename;
	_sprite = ImageFileCache::GetSprite(filename);
	_isLoaded = true;


}

void VisibleGameObject::Draw(sf::RenderWindow & renderWindow)
{
	if(_isLoaded)
	{
		renderWindow.Draw(_sprite);
	}
}

void VisibleGameObject::Update(float elapsedTime)
{
}

float VisibleGameObject::GetHeight() const
{
	return _sprite.GetSize().y;
}

float VisibleGameObject::GetWidth() const
{
	return _sprite.GetSize().x;
}

sf::Rect<float> VisibleGameObject::GetBoundingRect() const
{
	sf::Vector2f size = _sprite.GetSize();
	sf::Vector2f position = _sprite.GetPosition();

	return sf::Rect<float>(
			position.x - size.x/2,
			position.y - size.y/2,
			position.x + size.x/2,
			position.y + size.y/2
			);
}

void VisibleGameObject::SetPosition(float x, float y)
{
	if (_isLoaded)
	{
		_sprite.SetPosition(x,y);
	}
}

sf::Vector2f VisibleGameObject::GetPosition() const
{
	if(_isLoaded)
	{
		return _sprite.GetPosition();
	}
	return sf::Vector2f();
}

sf::Sprite& VisibleGameObject::GetSprite()
{
	return _sprite;
}

bool VisibleGameObject::IsLoaded() const
{
	return _isLoaded;
}
