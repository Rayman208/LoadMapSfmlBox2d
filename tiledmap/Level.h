#pragma once

#include <SFML\Graphics.hpp>
#include <pugixml.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace sf;
using namespace pugi;
using namespace std;

class Level
{
private:
	vector<Sprite*> _tiles;
	Vector2i _levelSize;
public:
	Level();
	~Level();

	void LoadLevel(string fileName);

	Sprite GetTileByIndex(int index);
	int GetTilesCount();

	Vector2i GetLevelSize();
};

