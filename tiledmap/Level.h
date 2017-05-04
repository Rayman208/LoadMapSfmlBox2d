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

struct Object
{
	string name;
	int x, y, width, height;
};

class Level
{
private:
	vector<Sprite*> _tiles;
	Vector2i _levelSize;

	vector<Object> _objects;
	Object _player;
public:
	Level();
	~Level();

	void LoadLevel(string fileName);

	Sprite GetTileByIndex(int index);
	int GetTilesCount();

	Vector2i GetLevelSize();

	Object GetObjectByIndex(int index);
	int GetObjectsCount();

	Object GetPlayer();
};

