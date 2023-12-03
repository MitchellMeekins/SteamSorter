#include "texturemanager.h"
map<string, sf::Texture> TextureManager::textureMap;
Texture& TextureManager::textureGetter(string directory)
{
	if (textureMap.find(directory) == textureMap.end())
	{
		LoadMap(directory);
	}

	return textureMap[directory];
}

void TextureManager::Clear()
{
	textureMap.clear();
}

void TextureManager::LoadMap(string directory)
{
	string path = "";
	path = "files/images/" + directory;
	path += ".png";
	textureMap[directory].loadFromFile(path);
}
