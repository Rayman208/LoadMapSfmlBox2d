#include "Level.h"

void main()
{
	Level lvl;
	lvl.LoadLevel("map.tmx");
	int w = lvl.GetLevelSize().x;
	int h = lvl.GetLevelSize().y;

	RenderWindow window(VideoMode(w, h), "Sergey");
	Clock clk;
	float deltaTime;

	while (window.isOpen())
	{
		Event evt;
		while (window.pollEvent(evt))
		{
			if (evt.type == Event::Closed)
			{
				window.close();
			}
		}
		deltaTime = clk.restart().asSeconds();
		window.setTitle("FPS: " + to_string(1.0 / deltaTime));

		window.clear();
		for (int i = 0; i < lvl.GetTilesCount(); i++)
		{
			window.draw(lvl.GetTileByIndex(i));
		}
		window.display();
	}
}