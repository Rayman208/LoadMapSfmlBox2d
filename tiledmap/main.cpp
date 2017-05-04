#include "Level.h"
#include <Box2D\Box2D.h>

#include "ContactListener.h"

const float PtM = 0.04f;
const float MtP = 25.0f;

b2Body* CreateSquareBody(b2World &world, float x, float y, float w, float h, char* userData, b2BodyType type)
{
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape polygonShape;

	float hw = (w / 2.0f), hh = (h / 2.0f);

	bodyDef.position = b2Vec2((x+hw)*PtM, (y+hh)*PtM);
	bodyDef.type = type;

	polygonShape.SetAsBox(hw*PtM, hh*PtM);
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 1.0f;
//	fixtureDef.friction = 0.7f;
	fixtureDef.userData = userData;

	b2Body *body = world.CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);
	body->SetUserData(userData);


	return body;
}


void main()
{
	Level lvl;
	lvl.LoadLevel("map.tmx");
	int w = lvl.GetLevelSize().x;
	int h = lvl.GetLevelSize().y;

	RenderWindow window(VideoMode(w, h), "Sergey");
	window.setFramerateLimit(60);

	Texture playerTexture;
	playerTexture.loadFromFile("sonic.png");

	Sprite playerSprite;
	playerSprite.setTexture(playerTexture);

	playerSprite.setOrigin
	(
		lvl.GetPlayer().width / 2,
		lvl.GetPlayer().height / 2
	);
	b2Vec2 gravity(0.0f, 9.8f);
	b2World world(gravity);

	ContactListener m_ContactListener(&world);
	world.SetContactListener(&m_ContactListener);

	for (int i = 0; i < lvl.GetObjectsCount(); i++)
	{
		Object temp = lvl.GetObjectByIndex(i);
		
		CreateSquareBody(world, 
			temp.x, temp.y, 
			temp.width, temp.height, 
			/*(char*)temp.name.c_str()*/"solid",
			b2BodyType::b2_staticBody);
	}

	b2Body *playerBody = CreateSquareBody(world,
		lvl.GetPlayer().x, lvl.GetPlayer().y,
		lvl.GetPlayer().width, lvl.GetPlayer().height,
		/*(char*)lvl.GetPlayer().name.c_str()*/"player",
		b2BodyType::b2_dynamicBody);

	while (window.isOpen())
	{
		Event evt;
		while (window.pollEvent(evt))
		{
			if (evt.type == Event::Closed)
			{
				window.close();
			}
			if (evt.type == Event::KeyPressed)
			{
				switch (evt.key.code)
				{
				case Keyboard::Key::Left:
					playerBody->ApplyForceToCenter(b2Vec2(-50.f, 0), true);
					break;

				case Keyboard::Key::Right:
					playerBody->ApplyForceToCenter(b2Vec2(50.f, 0), true);
					break;

				case Keyboard::Key::Space:
					playerBody->ApplyForceToCenter(b2Vec2(0.f, -150.f), true);
					break;
				}
			}
		}
		world.Step(1.0f / 60.0f, 8, 3);

		window.clear();
		for (int i = 0; i < lvl.GetTilesCount(); i++)
		{
			window.draw(lvl.GetTileByIndex(i));
		}

		playerSprite.setPosition
		(
			playerBody->GetPosition().x*MtP,
			playerBody->GetPosition().y*MtP
		);
		window.draw(playerSprite);

		window.display();

	}
}