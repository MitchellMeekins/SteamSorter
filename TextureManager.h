#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;
using namespace sf;

struct TextureManager
{
	static Texture& textureGetter(string directory);
	static void Clear();
private:
	static map<string, Texture> textureMap;
	static void LoadMap(string directory);
};