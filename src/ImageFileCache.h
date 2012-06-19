#pragma once
#include "stdafx.h"

class ImageFileCache
{
	public:
		static void FlushCache();
		static sf::Sprite GetSprite(std::string filename);

	private:
		static std::map<std::string,sf::Image*> images;

		template <typename T>
			struct Deallocator{
				void operator()(const std::pair<std::string,T> &p)
				{
					delete p.second;
				}
		};
};

class ImageNotFoundException : public std::runtime_error
{
	public:
		ImageNotFoundException(std::string const& msg):
			std::runtime_error(msg)
	{}
};
