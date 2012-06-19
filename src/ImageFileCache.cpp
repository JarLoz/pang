#include "ImageFileCache.h"

void ImageFileCache::FlushCache()
{
	std::for_each(images.begin(), images.end(), Deallocator<sf::Image*>());
}
sf::Sprite ImageFileCache::GetSprite(std::string filename)
{
	std::map<std::string,sf::Image*>::iterator itr = images.find(filename);

	if(itr == images.end())
	{
		sf::Image* image = new sf::Image();
		if(!image->LoadFromFile(filename))
		{
			delete image;
			throw ImageNotFoundException(filename + " was not found!");
		}

		std::map<std::string,sf::Image*>::iterator res 
			= images.insert(std::pair<std::string,sf::Image*>(filename, image)).first;

		sf::Sprite sprite;
		sprite.SetImage(*image);
		return sprite;
	}
	else
	{
		sf::Sprite sprite;
		sprite.SetImage(*itr->second);
		return sprite;
	}

	throw ImageNotFoundException(filename + " was not found!");

}
std::map<std::string,sf::Image*> ImageFileCache::images;
